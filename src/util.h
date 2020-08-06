#ifndef _UTIL_H_
#define _UTIL_H_

#include <gdkmm.h>
#include <glibmm.h>
#include <string>
#include <utility>

namespace AhoViewer
{
    enum class ZoomMode : char
    {
        AUTO_FIT   = 'A',
        FIT_WIDTH  = 'W',
        FIT_HEIGHT = 'H',
        MANUAL     = 'M',
    };
    struct Note
    {
        Note(std::string body, const int w, const int h, const int x, const int y)
            : body{ std::move(body) },
              w{ w },
              h{ h },
              x{ x },
              y{ y }
        {
        }
        std::string body;
        int w, h, x, y;
    };
    struct ScrollPos
    {
        ScrollPos(const double h, const double v, const ZoomMode zoom)
            : h{ h },
              v{ v },
              zoom{ zoom }
        {
        }
        double h, v;
        ZoomMode zoom;
    };

    namespace Booru
    {
        enum class Rating
        {
            SAFE         = 0,
            QUESTIONABLE = 1,
            EXPLICIT     = 2,
        };
        enum class Type
        {
            UNKNOWN     = -1,
            DANBOORU_V2 = 0,
            GELBOORU    = 1,
            MOEBOORU    = 2,
            SHIMMIE     = 3,
            DANBOORU    = 4,
        };
        struct Tag
        {
            // These values determine the order when sorting by type
            // They do not reflect the actual value of Gelbooru's type attribute,
            // that is converted when the tag list is retrieved
            enum class Type
            {
                ARTIST     = 0,
                CHARACTER  = 1,
                COPYRIGHT  = 2,
                METADATA   = 3,
                GENERAL    = 4,
                DEPRECATED = 5,
                UNKNOWN    = 6,
            };

            Tag() = default;
            Tag(std::string tag, const Type type = Type::UNKNOWN)
                : tag{ std::move(tag) },
                  type{ type }
            {
            }
            Tag(const Tag& orig) = default;

            friend std::istream& operator>>(std::istream& in, Tag& e);
            friend std::ostream& operator<<(std::ostream& out, const Tag& e);

            operator std::string() const { return tag; }
            operator Glib::ustring() const { return tag; }
            operator Gdk::RGBA() const;

            inline bool operator==(const Tag& rhs) const { return tag == rhs.tag; }
            inline bool operator!=(const Tag& rhs) const { return !(*this == rhs); }
            inline bool operator<(const Tag& rhs) const { return tag.compare(rhs.tag) < 0; }
            inline bool operator>(const Tag& rhs) const { return tag.compare(rhs.tag) > 0; }
            inline bool operator<=(const Tag& rhs) const { return tag.compare(rhs.tag) <= 0; }
            inline bool operator>=(const Tag& rhs) const { return tag.compare(rhs.tag) >= 0; }

            std::string tag;
            mutable Type type{ Type::UNKNOWN };
        };
        enum class TagViewOrder
        {
            TYPE = 0,
            TAG  = 1,
        };
    }
}

#endif /* _UTIL_H_ */
