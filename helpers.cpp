#include <unordered_map>
#include <string>
#if defined(_WIN32)
// Workaround for "combaseapi.h(229): error C2187: 
// syntax error: 'identifier' was unexpected here" when using /permissive-
struct IUnknown; 
#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#endif

#include "helpers.h"

using namespace std;

// HTML Colors helpers
static unordered_map<string, ColorValues> htmlColorsTable {
    {"Black", {0x000000, 0, 0, 0}},
    {"Navy", {0x000080, 0, 0, 128}},
    {"DarkBlue", {0x00008B, 0, 0, 139}},
    {"MediumBlue", {0x0000CD, 0, 0, 205}},
    {"Blue", {0x0000FF, 0, 0, 255}},
    {"DarkGreen", {0x006400, 0, 100, 0}},
    {"Green", {0x008000, 0, 128, 0}},
    {"Teal", {0x008080, 0, 128, 128}},
    {"DarkCyan", {0x008B8B, 0, 139, 139}},
    {"DeepSkyBlue", {0x00BFFF, 0, 191, 255}},
    {"DarkTurquoise", {0x00CED1, 0, 206, 209}},
    {"MediumSpringGreen", {0x00FA9A, 0, 250, 154}},
    {"Lime", {0x00FF00, 0, 255, 0}},
    {"SpringGreen", {0x00FF7F, 0, 255, 127}},
    {"Aqua", {0x00FFFF, 0, 255, 255}},
    {"Cyan", {0x00FFFF, 0, 255, 255}},
    {"MidnightBlue", {0x191970, 25, 25, 112}},
    {"DodgerBlue", {0x1E90FF, 30, 144, 255}},
    {"LightSeaGreen", {0x20B2AA, 32, 178, 170}},
    {"ForestGreen", {0x228B22, 34, 139, 34}},
    {"SeaGreen", {0x2E8B57, 46, 139, 87}},
    {"DarkSlateGray", {0x2F4F4F, 47, 79, 79}},
    {"DarkSlateGrey", {0x2F4F4F, 47, 79, 79}},
    {"LimeGreen", {0x32CD32, 50, 205, 50}},
    {"MediumSeaGreen", {0x3CB371, 60, 179, 113}},
    {"Turquoise", {0x40E0D0, 64, 224, 208}},
    {"RoyalBlue", {0x4169E1, 65, 105, 225}},
    {"SteelBlue", {0x4682B4, 70, 130, 180}},
    {"DarkSlateBlue", {0x483D8B, 72, 61, 139}},
    {"MediumTurquoise", {0x48D1CC, 72, 209, 204}},
    {"Indigo ", {0x4B0082, 75, 0, 130}},
    {"DarkOliveGreen", {0x556B2F, 85, 107, 47}},
    {"CadetBlue", {0x5F9EA0, 95, 158, 160}},
    {"CornflowerBlue", {0x6495ED, 100, 149, 237}},
    {"RebeccaPurple", {0x663399, 102, 51, 153}},
    {"MediumAquaMarine", {0x66CDAA, 102, 205, 170}},
    {"DimGray", {0x696969, 105, 105, 105}},
    {"DimGrey", {0x696969, 105, 105, 105}},
    {"SlateBlue", {0x6A5ACD, 106, 90, 205}},
    {"OliveDrab", {0x6B8E23, 107, 142, 35}},
    {"SlateGray", {0x708090, 112, 128, 144}},
    {"SlateGrey", {0x708090, 112, 128, 144}},
    {"LightSlateGray", {0x778899, 119, 136, 153}},
    {"LightSlateGrey", {0x778899, 119, 136, 153}},
    {"MediumSlateBlue", {0x7B68EE, 123, 104, 238}},
    {"LawnGreen", {0x7CFC00, 124, 252, 0}},
    {"Chartreuse", {0x7FFF00, 127, 255, 0}},
    {"Aquamarine", {0x7FFFD4, 127, 255, 212}},
    {"Maroon", {0x800000, 128, 0, 0}},
    {"Purple", {0x800080, 128, 0, 128}},
    {"Olive", {0x808000, 128, 128, 0}},
    {"Gray", {0x808080, 128, 128, 128}},
    {"Grey", {0x808080, 128, 128, 128}},
    {"SkyBlue", {0x87CEEB, 135, 206, 235}},
    {"LightSkyBlue", {0x87CEFA, 135, 206, 250}},
    {"BlueViolet", {0x8A2BE2, 138, 43, 226}},
    {"DarkRed", {0x8B0000, 139, 0, 0}},
    {"DarkMagenta", {0x8B008B, 139, 0, 139}},
    {"SaddleBrown", {0x8B4513, 139, 69, 19}},
    {"DarkSeaGreen", {0x8FBC8F, 143, 188, 143}},
    {"LightGreen", {0x90EE90, 144, 238, 144}},
    {"MediumPurple", {0x9370DB, 147, 112, 219}},
    {"DarkViolet", {0x9400D3, 148, 0, 211}},
    {"PaleGreen", {0x98FB98, 152, 251, 152}},
    {"DarkOrchid", {0x9932CC, 153, 50, 204}},
    {"YellowGreen", {0x9ACD32, 154, 205, 50}},
    {"Sienna", {0xA0522D, 160, 82, 45}},
    {"Brown", {0xA52A2A, 165, 42, 42}},
    {"DarkGray", {0xA9A9A9, 169, 169, 169}},
    {"DarkGrey", {0xA9A9A9, 169, 169, 169}},
    {"LightBlue", {0xADD8E6, 173, 216, 230}},
    {"GreenYellow", {0xADFF2F, 173, 255, 47}},
    {"PaleTurquoise", {0xAFEEEE, 175, 238, 238}},
    {"LightSteelBlue", {0xB0C4DE, 176, 196, 222}},
    {"PowderBlue", {0xB0E0E6, 176, 224, 230}},
    {"FireBrick", {0xB22222, 178, 34, 34}},
    {"DarkGoldenRod", {0xB8860B, 184, 134, 11}},
    {"MediumOrchid", {0xBA55D3, 186, 85, 211}},
    {"RosyBrown", {0xBC8F8F, 188, 143, 143}},
    {"DarkKhaki", {0xBDB76B, 189, 183, 107}},
    {"Silver", {0xC0C0C0, 192, 192, 192}},
    {"MediumVioletRed", {0xC71585, 199, 21, 133}},
    {"IndianRed ", {0xCD5C5C, 205, 92, 92}},
    {"Peru", {0xCD853F, 205, 133, 63}},
    {"Chocolate", {0xD2691E, 210, 105, 30}},
    {"Tan", {0xD2B48C, 210, 180, 140}},
    {"LightGray", {0xD3D3D3, 211, 211, 211}},
    {"LightGrey", {0xD3D3D3, 211, 211, 211}},
    {"Thistle", {0xD8BFD8, 216, 191, 216}},
    {"Orchid", {0xDA70D6, 218, 112, 214}},
    {"GoldenRod", {0xDAA520, 218, 165, 32}},
    {"PaleVioletRed", {0xDB7093, 219, 112, 147}},
    {"Crimson", {0xDC143C, 220, 20, 60}},
    {"Gainsboro", {0xDCDCDC, 220, 220, 220}},
    {"Plum", {0xDDA0DD, 221, 160, 221}},
    {"BurlyWood", {0xDEB887, 222, 184, 135}},
    {"LightCyan", {0xE0FFFF, 224, 255, 255}},
    {"Lavender", {0xE6E6FA, 230, 230, 250}},
    {"DarkSalmon", {0xE9967A, 233, 150, 122}},
    {"Violet", {0xEE82EE, 238, 130, 238}},
    {"PaleGoldenRod", {0xEEE8AA, 238, 232, 170}},
    {"LightCoral", {0xF08080, 240, 128, 128}},
    {"Khaki", {0xF0E68C, 240, 230, 140}},
    {"AliceBlue", {0xF0F8FF, 240, 248, 255}},
    {"HoneyDew", {0xF0FFF0, 240, 255, 240}},
    {"Azure", {0xF0FFFF, 240, 255, 255}},
    {"SandyBrown", {0xF4A460, 244, 164, 96}},
    {"Wheat", {0xF5DEB3, 245, 222, 179}},
    {"Beige", {0xF5F5DC, 245, 245, 220}},
    {"WhiteSmoke", {0xF5F5F5, 245, 245, 245}},
    {"MintCream", {0xF5FFFA, 245, 255, 250}},
    {"GhostWhite", {0xF8F8FF, 248, 248, 255}},
    {"Salmon", {0xFA8072, 250, 128, 114}},
    {"AntiqueWhite", {0xFAEBD7, 250, 235, 215}},
    {"Linen", {0xFAF0E6, 250, 240, 230}},
    {"LightGoldenRodYellow", {0xFAFAD2, 250, 250, 210}},
    {"OldLace", {0xFDF5E6, 253, 245, 230}},
    {"Red", {0xFF0000, 255, 0, 0}},
    {"Fuchsia", {0xFF00FF, 255, 0, 255}},
    {"Magenta", {0xFF00FF, 255, 0, 255}},
    {"DeepPink", {0xFF1493, 255, 20, 147}},
    {"OrangeRed", {0xFF4500, 255, 69, 0}},
    {"Tomato", {0xFF6347, 255, 99, 71}},
    {"HotPink", {0xFF69B4, 255, 105, 180}},
    {"Coral", {0xFF7F50, 255, 127, 80}},
    {"DarkOrange", {0xFF8C00, 255, 140, 0}},
    {"LightSalmon", {0xFFA07A, 255, 160, 122}},
    {"Orange", {0xFFA500, 255, 165, 0}},
    {"LightPink", {0xFFB6C1, 255, 182, 193}},
    {"Pink", {0xFFC0CB, 255, 192, 203}},
    {"Gold", {0xFFD700, 255, 215, 0}},
    {"PeachPuff", {0xFFDAB9, 255, 218, 185}},
    {"NavajoWhite", {0xFFDEAD, 255, 222, 173}},
    {"Moccasin", {0xFFE4B5, 255, 228, 181}},
    {"Bisque", {0xFFE4C4, 255, 228, 196}},
    {"MistyRose", {0xFFE4E1, 255, 228, 225}},
    {"BlanchedAlmond", {0xFFEBCD, 255, 235, 205}},
    {"PapayaWhip", {0xFFEFD5, 255, 239, 213}},
    {"LavenderBlush", {0xFFF0F5, 255, 240, 245}},
    {"SeaShell", {0xFFF5EE, 255, 245, 238}},
    {"Cornsilk", {0xFFF8DC, 255, 248, 220}},
    {"LemonChiffon", {0xFFFACD, 255, 250, 205}},
    {"FloralWhite", {0xFFFAF0, 255, 250, 240}},
    {"Snow", {0xFFFAFA, 255, 250, 250}},
    {"Yellow", {0xFFFF00, 255, 255, 0}},
    {"LightYellow", {0xFFFFE0, 255, 255, 224}},
    {"Ivory", {0xFFFFF0, 255, 255, 240}},
    {"White", {0xFFFFFF, 255, 255, 255}}
};

bool isValidHtmlColorName(const string& colorName) noexcept {
    return (htmlColorsTable.count(colorName) == 1);
}

ColorValues htmlColorNameToValues(const string& colorName) {
    string msg;

    if (! isValidHtmlColorName(colorName)) {
        msg = colorName + " is not a valid HTML color name";
        throw ErrorColor(msg.c_str());
    }

    return htmlColorsTable[colorName];
}

// Ascii drawing helper
void coutColoredBlock(const ColorValues& color) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOutput, &csbInfo);

    WORD wAttributes = 0;
    if (color.redValue > 128) { wAttributes  = wAttributes  | FOREGROUND_RED; }
    if (color.greenValue > 128) { wAttributes  = wAttributes  | FOREGROUND_GREEN; }
    if (color.blueValue > 128) { wAttributes  = wAttributes  | FOREGROUND_BLUE; }
    if ((color.redValue + color.greenValue + color.blueValue) > 384) {
        wAttributes  = wAttributes  | FOREGROUND_INTENSITY;
    }
    
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
#else
#endif

    cout << string(1, BLOCK) << flush;

#if defined(_WIN32)
    SetConsoleTextAttribute(hConsoleOutput, csbInfo.wAttributes);
#else
#endif
}
