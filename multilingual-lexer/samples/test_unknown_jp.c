// Test file with some known JP keywords and unknown ones to trigger AI phase
// Known: もし, 表示, 戻る
// Unknown: 関数, 変数, 出力する

関数 main() {
    変数 x = 5;
    もし (x > 3) {
        表示("Hello World\n");
        出力する("Done");
    }
    戻る 0;
}