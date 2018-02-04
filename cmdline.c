#include <stdio.h>
#include <string.h>

#define HELP_MSG \
"# ֧�ֵ������и���\n" \
"\n" \
"* h version\n" \
"* h help\n" \
"* h file ... print ...\n" \
"* h file ... replace ...\n" \
"* h file ... delete ...\n" \
"* h file ... insert ...\n" \
"\n" \
"# ��ϸ\n" \
"\n" \
"* version\n" \
"  > ��ʾ�汾��Ϣ\n" \
"\n" \
"* help\n" \
"  > ��ʾ�����а���\n" \
"\n" \
"* file <FILENAME>\n" \
"  > ָ��Ŀ���ļ���\n" \
"\n" \
"* print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]\n" \
"  > ָ����ʽ��ʾĿ���ļ�����\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * <start> <len> <end>�������޷���ʮ��������,Ҳ������0x��ͷ��16��������.\n" \
"    * Ĭ����ʾ�����ļ�.\n" \
"    * ָֻ��<start>��Ӹõ�ַ��ʾ���ļ�β.\n" \
"  * <FORMAT>: bin1|bin8|bin16|bin32|bin64\n" \
"              oct8|oct16|oct32|oct64\n" \
"              hex8|hex16|hex32|hex64\n" \
"              int8|int16|int32|int64\n" \
"              uint8|uint16|uint32|uint64\n" \
"              fix8.d|fix16.d|fix32.d|fix64.d\n" \
"              ufix8.d|ufix16.d|ufix32.d|ufix64.d\n" \
"              float|single|double\n" \
"    * Ĭ��<FORMAT>��\"hex8\".\n" \
"    * fix��ʾ����С��,ʮ������\"d\"��������������С����λ��.\n" \
"  * <ENDIAN>: big|little\n" \
"  * <ADDRDISP>: addr\n" \
"    * �Ա����ʽ��ʾ����,�������ַ.\n" \
"    * Ĭ�ϲ�������ݵ�ַ.\n" \
"  * <COLORDISP>: colorblind|background|foreground\n" \
"    * ���������������������ʾ.\n" \
"    * \"colorblind\"��ʾ������ɫ����,\"foreground\"��ʾ��ǰ��ɫ����,\"background\"��ʾ�Ա���ɫ����.\n" \
"    * Ĭ�ϵ�<COLORDISP>��\"colorblind\".\n" \
"  * <PAGEDDISP>: paged\n" \
"    * ���������Ƿ��ҳ��ʾ.\n" \
"    * Ĭ�ϲ���ҳ��ʾ.\n" \
"\n" \
"* replace <ADDR> <DATA>\n" \
"* replace <ADDR> <FILENAME> [<FILEADDR>]\n" \
"  > ��дĿ���ļ��Ĳ�������,����ԭ�ز���\n" \
"  * <ADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * ����Ҫ���滻�����ݶ�.\n" \
"    * ָֻ��<start>���滻�õ�ַ���ļ�β����������.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"    * <byte>�ǿո�ָ��ʮ����������(����0xǰ׺).\n" \
"  * <FILENAME>: <filename>\n" \
"    * ָ��Ҫ�滻������Դ�ļ���.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * ����Ҫ�����滻��Դ�ļ����ݶ�.\n" \
"    * Ĭ�Ͻ������ļ������滻.\n" \
"    * ָֻ��<start>,��Դ�ļ����ݶ��ǴӸõ�ַ��Դ�ļ�β����������.\n" \
"\n" \
"* delete <ADDR>\n" \
"  > ɾ��Ŀ���ļ���һ����,����ԭ�ز���\n" \
"  * <ADDR>: @<start>[,<end>] | @<start>-<end>\n" \
"    * ָ��Ҫɾ����Ŀ���ļ����ݶ�.\n" \
"    * ָֻ��<start>�Ὣ�õ�ַ���ļ�β������ȫ��ɾ��.\n" \
"\n" \
"* insert <LOCATOR> <DATA>\n" \
"* insert <LOCATOR> <FILENAME> [<FILEADDR>]\n" \
"  > ��Ŀ���ļ��в�������,����ԭ�ز���\n" \
"  * <LOCATOR>: @<start>\n" \
"    * ָ��Ҫ�������ݵ��׵�ַ.\n" \
"    * \"@head\"��ʾ���뵽�ļ�ͷ,\"@tail\"��ʾ���뵽�ļ�β.\n" \
"  * <DATA>: <byte> ... <byte>\n" \
"  * <FILENAME>: <filename>\n" \
"    * ָ��Ҫ���������Դ�ļ�.\n" \
"  * <FILEADDR>: @<start>[,<len>] | @<start>-<end>\n" \
"    * ����Ҫ���ڲ����Դ�ļ����ݶ�.\n" \
"    * Ĭ�ϲ��������ļ�.\n" \
"    * ָֻ��<start>,��Դ�ļ����ݶ��ǴӸõ�ַ��Դ�ļ�β����������.\n"

// ���������в���
int parse(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

// ��ʾ������Ϣ(Horizontal & vertical scrollable)
int prn_help_msg(void){
    
}

int main(int argc, char* argv[]){
    printf(HELP_MSG);
    return 0;
}