#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "sdk/global.h"
#include "sdk/DPTR.h"
#include "sdk/mediainfo.h"
#include "Packet.h"

NAMESPACE_BEGIN

enum SubtitleType {
    SubtitleText,
    SubtitleAss,
    SubtitlePixmap
};

struct SubtitleFrame {
    SubtitleFrame():
        begin(0.0),
        end(0.0),
        type(SubtitleText)
    {

    }

    bool isValid() const {return begin < end;}
    operator bool() const {return isValid();}
    inline bool operator < (const SubtitleFrame &f) const {return end < f.end;}
    inline bool operator < (double t) const {return end < t;}

    SubtitleType type;
    double begin, end;
    std::string text;
};

class SubtitlePrivate;
class Subtitle
{
    DPTR_DECLARE_PRIVATE(Subtitle)
public:
    Subtitle();
    ~Subtitle();

    bool enabled() const;
    void setEnabled(bool b);
    void setFile(const std::string &name);
    void setCodec(const std::string &codec);
    void load();
    bool processHeader(MediaInfo *info);
    bool processLine(Packet *pkt);

    void setTimestamp(double t);
    SubtitleFrame frame();

protected:

private:
    DPTR_DECLARE(Subtitle)
};

NAMESPACE_END
#endif //SUBTITLE_H