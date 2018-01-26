/*
 
 # ֧�ֵ������и���
 
 * h version
 * h help
 * h file ... print ...
 * h file ... replace ...
 * h file ... delete ...
 * h file ... insert ...
 
 # ��ϸ
 
 * version
   > ��ʾ�汾��Ϣ

 * help
   > ��ʾ�����а���

 * file <FILENAME>
   > ָ��Ŀ���ļ���

 * print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<ADDRDISP>] [<COLORDISP>] [<PAGEDDISP>]
   > ָ����ʽ��ʾĿ���ļ�����
   * <ADDR>: @<start>[,<len>] | @<start>-<end>
     * <start> <len> <end>�������޷���ʮ��������,Ҳ������0x��ͷ��16��������.
     * Ĭ����ʾ�����ļ�.
     * ָֻ��<start>��Ӹõ�ַ��ʾ���ļ�β.
   * <FORMAT>: bin1|bin8|bin16|bin32|bin64
               oct8|oct16|oct32|oct64
               hex8|hex16|hex32|hex64
               int8|int16|int32|int64
               uint8|uint16|uint32|uint64
               fix8.d|fix16.d|fix32.d|fix64.d
               ufix8.d|ufix16.d|ufix32.d|ufix64.d
               float|single|double
     * Ĭ��<FORMAT>��"hex8".
     * fix��ʾ����С��,ʮ������"d"��������������С����λ��.
   * <ENDIAN>: big|little
   * <ADDRDISP>: addr
     * �Ա����ʽ��ʾ����,�������ַ.
     * Ĭ�ϲ�������ݵ�ַ.
   * <COLORDISP>: colorblind|background|foreground
     * ���������������������ʾ.
     * "colorblind"��ʾ������ɫ����,"foreground"��ʾ��ǰ��ɫ����,"background"��ʾ�Ա���ɫ����.
     * Ĭ�ϵ�<COLORDISP>��"colorblind".
   * <PAGEDDISP>: paged
     * ���������Ƿ��ҳ��ʾ.
     * Ĭ�ϲ���ҳ��ʾ.

 * replace <ADDR> <DATA>
 * replace <ADDR> <FILENAME> [<FILEADDR>]
   > ��дĿ���ļ��Ĳ�������,����ԭ�ز���
   * <ADDR>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ���滻�����ݶ�.
     * ָֻ��<start>���滻�õ�ַ���ļ�β����������.
   * <DATA>: <byte> ... <byte>
     * <byte>�ǿո�ָ��ʮ����������(����0xǰ׺).
   * <FILENAME>: <filename>
     * ָ��Ҫ�滻������Դ�ļ���.
   * <FILEADDR>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ�����滻��Դ�ļ����ݶ�.
     * Ĭ�Ͻ������ļ������滻.
     * ָֻ��<start>,��Դ�ļ����ݶ��ǴӸõ�ַ��Դ�ļ�β����������.

 * delete <ADDR>
   > ɾ��Ŀ���ļ���һ����,����ԭ�ز���
   * <ADDR>: @<start>[,<end>] | @<start>-<end>
     * ָ��Ҫɾ����Ŀ���ļ����ݶ�.
     * ָֻ��<start>�Ὣ�õ�ַ���ļ�β������ȫ��ɾ��.

 * insert <LOCATOR> <DATA>
 * insert <LOCATOR> <FILENAME> [<FILEADDR>]
   > ��Ŀ���ļ��в�������,����ԭ�ز���
   * <LOCATOR>: @<start>
     * ָ��Ҫ�������ݵ��׵�ַ.
     * "@head"��ʾ���뵽�ļ�ͷ,"@tail"��ʾ���뵽�ļ�β.
   * <DATA>: <byte> ... <byte>
   * <FILENAME>: <filename>
     * ָ��Ҫ���������Դ�ļ�.
   * <FILEADDR>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ���ڲ����Դ�ļ����ݶ�.
     * Ĭ�ϲ��������ļ�.
     * ָֻ��<start>,��Դ�ļ����ݶ��ǴӸõ�ַ��Դ�ļ�β����������.

 */

#include <stdio.h>
#include <string.h>

// �ж�str�Ƿ���pattern��ͷ
int starts_with(const char* str, const char* pattern){
    for(int i=0;pattern[i];i++){
        if(pattern[i]^str[i])
            return 0;
    }
    return 1;
}

// ���������в���
int parser(int argc, char* argv[]){
    for(int i=0;i<argc;i++){
        // strcmp(argv[i],"--");
    }
    return 0;
}

int main(int argc, char* argv[]){
    printf("%d\n",starts_with("asd","ad"));
    return 0;
}