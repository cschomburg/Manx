#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QBuffer>
#include <QDataStream>

#include "nbtreader.h"
#include "zlib.h"

#include "nbttag/nbttags.h"

#define UNZIP_READ_BUFFER (256*1024)

NbtTag * NbtReader::readFile(const QString& filePath)
{
    QByteArray data;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open input file: %s", qPrintable(filePath));
        return 0;
    }

    quint64 compressedSize = file.size();

    uInt rep = compressedSize / UNZIP_READ_BUFFER;
    uInt rem = compressedSize % UNZIP_READ_BUFFER;
    uInt cur = 0;

    // extract data
    qint64 read;
    quint64 tot = 0;

    char buffer1[UNZIP_READ_BUFFER];
    char buffer2[UNZIP_READ_BUFFER];

    /* Allocate inflate state */
    z_stream zstr;
    zstr.zalloc = Z_NULL;
    zstr.zfree = Z_NULL;
    zstr.opaque = Z_NULL;
    zstr.next_in = Z_NULL;
    zstr.avail_in = 0;

    int zret;

    /*
     windowBits can also be greater than 15 for optional gzip decoding. Add
    32 to windowBits to enable zlib and gzip decoding with automatic header
    detection, or add 16 to decode only the gzip format (the zlib format will
    return a Z_DATA_ERROR.  If a gzip stream is being decoded, strm->adler is
    a crc32 instead of an adler32.
    */
    if ( (zret = inflateInit2_(&zstr, MAX_WBITS + 16, ZLIB_VERSION, sizeof(z_stream))) != Z_OK ) {
            qWarning("Failed to initialize zlib");
            return 0;
    }

    int szDecomp;

    // Decompress until deflate stream ends or end of file
    do
    {
            read = file.read(buffer1, cur < rep ? UNZIP_READ_BUFFER : rem);
            if (read == 0)
                    break;
            if (read < 0)
            {
                    (void)inflateEnd(&zstr);
                    qWarning("Read error");
                    return 0;
            }

            cur++;
            tot += read;

            zstr.avail_in = (uInt) read;
            zstr.next_in = (Bytef*) buffer1;


            // Run inflate() on input until output buffer not full
            do {
                    zstr.avail_out = UNZIP_READ_BUFFER;
                    zstr.next_out = (Bytef*) buffer2;;

                    zret = inflate(&zstr, Z_NO_FLUSH);

                    switch (zret) {
                            case Z_NEED_DICT:
                            case Z_DATA_ERROR:
                            case Z_MEM_ERROR:
                                    inflateEnd(&zstr);
                                    qWarning("zlib failed to decode file");
                                    return 0;
                            default:
                                    ;
                    }

                    szDecomp = UNZIP_READ_BUFFER - zstr.avail_out;
                    data.append(buffer2, szDecomp);
            } while (zstr.avail_out == 0);

    }
    while (zret != Z_STREAM_END);

    inflateEnd(&zstr);

    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);
    m_stream.setDevice(&buffer);

    return readTag();
}

char * NbtReader::readString()
{
    qint16 length;
    m_stream >> length;
    char *buffer = new char[length];
    m_stream.readRawData(buffer, length);
    buffer[length] = '\0';
    return buffer;
}

NbtTag * NbtReader::readTag(NbtTag::TagType tagType)
{
    const char *name = 0;
    if(tagType == NbtTag::TAG_Unknown) {
        qint8 tagRead;
        m_stream >> tagRead;
        tagType = NbtTag::TagType(tagRead);

        if(NbtTag::TagType(tagType) != NbtTag::TAG_End)
            name = readString();
    }

    NbtTag * tag = 0;

    qDebug(QString::number(tagType).toLatin1());
    if(name)
        qDebug(name);

    switch(NbtTag::TagType(tagType)) {
    case NbtTag::TAG_Byte: {
            qint8 byte;
            m_stream >> byte;
            tag = new NbtTagByte(byte, name);
            break;
        }
    case NbtTag::TAG_Short: {
            qint16 value;
            m_stream >> value;
            tag = new NbtTagShort(value, name);
            break;
        }
    case NbtTag::TAG_Int: {
            qint32 value;
            m_stream >> value;
            tag = new NbtTagInt(value, name);
            break;
        }
    case NbtTag::TAG_Long: {
            qint64 value;
            m_stream >> value;
            tag = new NbtTagLong(value, name);
            break;
        }
    case NbtTag::TAG_Float: {
            float value;
            m_stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
            m_stream >> value;
            tag = new NbtTagFloat(value, name);
            break;
        }
    case NbtTag::TAG_Double: {
            qreal value;
            m_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
            m_stream >> value;
            tag = new NbtTagDouble(value, name);
            break;
        }
    case NbtTag::TAG_Byte_Array: {
            qint32 length;
            m_stream >> length;

            char buffer[length];
            m_stream.readRawData(buffer, length);

            tag = new NbtTagByteArray(buffer, length, name);
            break;
        }
    case NbtTag::TAG_String: {
            const char *text = readString();
            tag = new NbtTagString(text, name);
            delete [] text;
            break;
        }
    case NbtTag::TAG_List: {
            qint8 childRead;
            m_stream >> childRead;
            NbtTag::TagType childType = NbtTag::TagType(childRead);

            qint32 length;
            m_stream >> length;

            NbtTagList *list = new NbtTagList(childType, name);

            for(int i=1; i <= length; i++) {
                NbtTag *child = readTag(childType);
                if(child)
                    list->add(child);
                else {
                    qWarning("NBT read error in TAG_List '%s' on element %d", name, length);
                    break;
                }
            }
            tag = list;
            break;
        }
    case NbtTag::TAG_Compound: {
            NbtTagCompound *compound = new NbtTagCompound(name);

            NbtTag *child = 0;
            while(child = readTag())
                    compound->add(child);
            tag = compound;
            break;
        }
    case NbtTag::TAG_End: {
            break;
        }
    default:
            qWarning("Unknown tagType '%d' for tag '%s'", tagType, name);
            break;
    }

    delete [] name;

    return tag;
}
