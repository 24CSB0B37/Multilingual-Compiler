#include "lang_config.h"
#include <string.h>
#include <stddef.h>

/* Language → C keywords */
static KeywordEntry jp_keywords[] = {
    {"もし", "if"},
    {"ならば", "else"},
    {"間", "while"},
    {"繰返す", "for"},
    {"戻る", "return"},
    {"返す", "return"},
    {"中断", "break"},
    {"継続", "continue"},
    {"切換", "switch"},
    {"場合", "case"},
    {"既定", "default"},
    {"列挙", "enum"},
    {"構造", "struct"},
    {"型", "typedef"},
    {"無効", "void"},
    {"長い", "long"},
    {"短い", "short"},
    {"符号なし", "unsigned"},
    {"符号付き", "signed"},
    {"定数", "const"},
    {"静的", "static"},
    {"整数", "int"},
    {"浮動", "float"},
    {"文字", "char"},
    {"二重", "double"},
    {"文字列", "string"},
    {"入力", "scanf"},
    {"出力", "printf"},
    {"インクルード", "include"},
    {"マクロ", "define"},
    {NULL, NULL}
};

static KeywordEntry hindi_keywords[] = {
    {"यदि", "if"},
    {"अन्यथा", "else"},
    {"जबतक", "while"},
    {"केलिए", "for"},
    {"लौटाओ", "return"},
    {"पूर्णांक", "int"},
    {"दशमलव", "float"},
    {"प्रदर्शित", "printf"},
    {"अक्षर", "char"},
    {"मौडल", "double"},
    {"संरचना", "struct"},
    {"टाइप", "typedef"},
    {"సಕ್ತ", "static"},
    {NULL, NULL}
};

static KeywordEntry telugu_keywords[] = {
    {"అయితే", "if"},
    {"లేకపోతే", "else"},
    {"ఉన్నంతవరకు", "while"},
    {"కోసం", "for"},
    {"తిరిగి", "return"},
    {"పూర్ణాంకం", "int"},
    {"దశాంశం", "float"},
    {"ప్రదర్శించు", "printf"},
    {"అక్షరం", "char"},
    {"డబుల్", "double"},
    {NULL, NULL}
};

static KeywordEntry tamil_keywords[] = {
    {"என்றால்", "if"},
    {"இல்லையெனில்", "else"},
    {"வரை", "while"},
    {"க்காக", "for"},
    {"திருப்பு", "return"},
    {"முழுஎண்", "int"},
    {"மிதவை", "float"},
    {"அச்சிடு", "printf"},
    {"எழுத்து", "char"},
    {"இரட்டை", "double"},
    {NULL, NULL}
};

static KeywordEntry kannada_keywords[] = {
    {"ಆದರೆ", "if"},
    {"ಇಲ್ಲವಾದರೆ", "else"},
    {"ಇರುವವರೆಗೆ", "while"},
    {"ಗಾಗಿ", "for"},
    {"ಹಿಂತಿರುಗಿ", "return"},
    {"ಪೂರ್ಣಾಂಕ", "int"},
    {"ದಶಮಾಂಶ", "float"},
    {"ಮುದ್ರಿಸಿ", "printf"},
    {"ಅಕ್ಷರ", "char"},
    {"ದ್ವಷ್ಟ", "double"},
    {NULL, NULL}
};

static KeywordEntry chinese_keywords[] = {
    {"如果", "if"},
    {"否则", "else"},
    {"当", "while"},
    {"对于", "for"},
    {"返回", "return"},
    {"中断", "break"},
    {"继续", "continue"},
    {"切换", "switch"},
    {"案例", "case"},
    {"默认", "default"},
    {"枚举", "enum"},
    {"结构", "struct"},
    {"类型定义", "typedef"},
    {"无效", "void"},
    {"长", "long"},
    {"短", "short"},
    {"无符号", "unsigned"},
    {"有符号", "signed"},
    {"常量", "const"},
    {"静态", "static"},
    {"整数", "int"},
    {"浮点", "float"},
    {"输出", "printf"},
    {"字符", "char"},
    {"双精度", "double"},
    {NULL, NULL}
};

static KeywordEntry korean_keywords[] = {
    {"만약", "if"},
    {"아니면", "else"},
    {"동안", "while"},
    {"위해", "for"},
    {"반환", "return"},
    {"정수", "int"},
    {"실수", "float"},
    {"출력", "printf"},
    {"문자", "char"},
    {"배정밀도", "double"},
    {NULL, NULL}
};

static KeywordEntry arabic_keywords[] = {
    {"إذا", "if"},
    {"وإلا", "else"},
    {"بينما", "while"},
    {"منأجل", "for"},
    {"إرجاع", "return"},
    {"توقف", "break"},
    {"استمر", "continue"},
    {"تبديل", "switch"},
    {"حالة", "case"},
    {"افتراضي", "default"},
    {"تعداد", "enum"},
    {"هيكل", "struct"},
    {"تعريفنوع", "typedef"},
    {"باطل", "void"},
    {"طويل", "long"},
    {"قصير", "short"},
    {"غيرموقع", "unsigned"},
    {"موقع", "signed"},
    {"ثابت", "const"},
    {"ثابتمحلي", "static"},
    {"عددصحيح", "int"},
    {"عددعشري", "float"},
    {"اطبع", "printf"},
    {"رمز", "char"},
    {"مزدوج", "double"},
    {NULL, NULL}
};

static KeywordEntry persian_keywords[] = {
    {"اگر", "if"},
    {"درغیراینصورت", "else"},
    {"تاوقتی", "while"},
    {"برای", "for"},
    {"بازگرداندن", "return"},
    {"عددصحیح", "int"},
    {"عدداعشاری", "float"},
    {"چاپ", "printf"},
    {"کاراکتر", "char"},
    {"دوبل", "double"},
    {NULL, NULL}
};

static KeywordEntry spanish_keywords[] = {
    {"si", "if"},
    {"sino", "else"},
    {"mientras", "while"},
    {"para", "for"},
    {"retornar", "return"},
    {"entero", "int"},
    {"flotante", "float"},
    {"imprimir", "printf"},
    {NULL, NULL}
};

static KeywordEntry french_keywords[] = {
    {"si", "if"},
    {"sinon", "else"},
    {"tantque", "while"},
    {"pour", "for"},
    {"retourner", "return"},
    {"entier", "int"},
    {"flottant", "float"},
    {"afficher", "printf"},
    {NULL, NULL}
};

static KeywordEntry german_keywords[] = {
    {"wenn", "if"},
    {"sonst", "else"},
    {"während", "while"},
    {"für", "for"},
    {"zurück", "return"},
    {"ganzzahl", "int"},
    {"gleitkomma", "float"},
    {"ausgeben", "printf"},
    {NULL, NULL}
};

static KeywordEntry russian_keywords[] = {
    {"если", "if"},
    {"иначе", "else"},
    {"пока", "while"},
    {"для", "for"},
    {"вернуть", "return"},
    {"целое", "int"},
    {"вещественное", "float"},
    {"печать", "printf"},
    {NULL, NULL}
};

static KeywordEntry turkish_keywords[] = {
    {"eger", "if"},
    {"degilse", "else"},
    {"surece", "while"},
    {"icin", "for"},
    {"dondur", "return"},
    {"tamsayi", "int"},
    {"ondalik", "float"},
    {"yazdir", "printf"},
    {NULL, NULL}
};

static KeywordEntry bengali_keywords[] = {
    {"যদি", "if"},
    {"নাহলে", "else"},
    {"যতক্ষণ", "while"},
    {"জন্য", "for"},
    {"ফেরত", "return"},
    {"পূর্ণসংখ্যা", "int"},
    {"দশমিক", "float"},
    {"প্রিন্ট", "printf"},
    {NULL, NULL}
};

static KeywordEntry marathi_keywords[] = {
    {"जर", "if"},
    {"अन्यथा", "else"},
    {"जोपर्यंत", "while"},
    {"साठी", "for"},
    {"परत", "return"},
    {"पूर्णांक", "int"},
    {"दशांश", "float"},
    {"छापा", "printf"},
    {NULL, NULL}
};

static KeywordEntry portuguese_keywords[] = {
    {"se", "if"},
    {"senao", "else"},
    {"enquanto", "while"},
    {"para", "for"},
    {"retornar", "return"},
    {"inteiro", "int"},
    {"flutuante", "float"},
    {"imprimir", "printf"},
    {NULL, NULL}
};

static KeywordEntry indonesian_keywords[] = {
    {"jika", "if"},
    {"selainitu", "else"},
    {"selama", "while"},
    {"untuk", "for"},
    {"kembali", "return"},
    {"bilanganbulat", "int"},
    {"pecahan", "float"},
    {"cetak", "printf"},
    {NULL, NULL}
};

static KeywordEntry vietnamese_keywords[] = {
    {"neu", "if"},
    {"neukhong", "else"},
    {"trongkhi", "while"},
    {"cho", "for"},
    {"trave", "return"},
    {"songuyen", "int"},
    {"sofloat", "float"},
    {"inra", "printf"},
    {NULL, NULL}
};

static KeywordEntry greek_keywords[] = {
    {"αν", "if"},
    {"αλλιως", "else"},
    {"ενω", "while"},
    {"για", "for"},
    {"επιστροφη", "return"},
    {"ακεραιος", "int"},
    {"πραγματικος", "float"},
    {"εκτυπωση", "printf"},
    {NULL, NULL}
};


const KeywordEntry* load_language(const char *lang) {
    if (!lang) return NULL;
    if (strcmp(lang, "jp") == 0) return jp_keywords;
    if (strcmp(lang, "hindi") == 0) return hindi_keywords;
    if (strcmp(lang, "telugu") == 0) return telugu_keywords;
    if (strcmp(lang, "tamil") == 0) return tamil_keywords;
    if (strcmp(lang, "kannada") == 0) return kannada_keywords;
    if (strcmp(lang, "chinese") == 0) return chinese_keywords;
    if (strcmp(lang, "korean") == 0) return korean_keywords;
    if (strcmp(lang, "arabic") == 0) return arabic_keywords;
    if (strcmp(lang, "persian") == 0) return persian_keywords;
    if (strcmp(lang, "spanish") == 0) return spanish_keywords;
    if (strcmp(lang, "french") == 0) return french_keywords;
    if (strcmp(lang, "german") == 0) return german_keywords;
    if (strcmp(lang, "russian") == 0) return russian_keywords;
    if (strcmp(lang, "turkish") == 0) return turkish_keywords;
    if (strcmp(lang, "bengali") == 0) return bengali_keywords;
    if (strcmp(lang, "marathi") == 0) return marathi_keywords;
    if (strcmp(lang, "portuguese") == 0) return portuguese_keywords;
    if (strcmp(lang, "indonesian") == 0) return indonesian_keywords;
    if (strcmp(lang, "vietnamese") == 0) return vietnamese_keywords;
    if (strcmp(lang, "greek") == 0) return greek_keywords;
    return NULL;
}
