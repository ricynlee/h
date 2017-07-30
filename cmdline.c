/*
 * version
    ��ʾ�汾��Ϣ

 * help
    ��ʾ����

�ļ�ģʽ
 * file <FILENAME>
    ָ��Ŀ���ļ���

 * print [<ADDR>] [<FORMAT>] [<ENDIAN>] [<BITWIDTH>] [<LABELDISP>] [<COLORDISP>] [<PAGEDDISP>]
    ָ����ʽ��ʾĿ���ļ�����
    <ADDR>: @<start>[,<len>] | @<start>-<end>
     * <start> <len> <end> ������ʮ��������,Ҳ������0x��ͷ��16��������.
     * Ĭ����ʾ�����ļ�.
    <FORMAT>: bin|oct|hex|dec[,signed]|dec,unsigned|fixed[,signed]|fixed,unsigned|float
     * Ĭ�� <FORMAT> �� "hex".
    <ENDIAN>: big|little
    <BITWIDTH>: <bitwidth>[.<decimalplace>]
     * <bitwidth> ������ 1,8,16,32,64
     * ����1��������<FORMAT>��"bin"�����.
     * ��<FORMAT>��"float"ʱ, ֻ��ѡ��32��64.Ĭ��<bitwidth>��8.
     * <decimalplace>����<FORMAT>��"fixed"����. Ĭ��<decimalplace>��0.
    <ADDRDISP>: addr:on|off
     * Ĭ��<ADDRDISP>��"on".
    <COLORDISP>: color:blind|color:background|color:foreground
     * ���������������������ʾ. Ĭ�ϵ� <COLORDISP> �� "colorblind".
    <PAGEDDISP>: paged:on|off
     * ���������Ƿ��ҳ��ʾ,Ĭ�Ͽ���.

 * replace <START> <DATA>
 * replace <ADDR> <FILENAME> [<ADDR_SRC>]
    �ȳ���дĿ���ļ��Ĳ�������,ԭ�ز���
    <START>: @<start>
    <DATA>: <byte> ... <byte>
     * <byte> �ǿո�ָ��ʮ����������(����0xǰ׺).
    <ADDR>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ���滻�����ݶ�.
    <FILENAME>: <filename>
     * ָ��Ҫ�滻������Դ�ļ���.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ�����滻��Դ�ļ����ݶ�.
     * <ADDR_SRC>��<ADDR>ָ���ĳ�����ؼ���.
     * Ĭ�Ͻ������ļ������滻.

 * append <DATA>
 * append <FILENAME> [<ADDR_SRC>]
    ��Ŀ���ļ���β׷�Ӷ�������
    <DATA>: <byte> ... <byte>
    <FILENAME>: <filename>
     * ָ��Ҫ׷�ӵ�����Դ�ļ�.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ����׷�ӵ�Դ�ļ����ݶ�.
     * Ĭ��׷�������ļ�.

 * delete <ADDR>
    ɾ��Ŀ���ļ���һ����,����ԭ�ز���
    <ADDR>: @<start>[,<end>] | @<start>-<end>
     * ָ��Ҫɾ����Ŀ���ļ����ݶ�.

 * insert [<START>] <DATA>
 * insert [<START>] <FILENAME> [<ADDR_SRC>]
    ��Ŀ���ļ��в�������,����ԭ�ز���
    <START>: @<start>
     * ָ��Ҫ�������ݵ��׵�ַ.
     * Ĭ�ϲ��뵽�ļ�ͷ.
    <DATA>: <byte> ... <byte>
    <FILENAME>: <filename>
     * ָ��Ҫ���������Դ�ļ�.
    <ADDR_SRC>: @<start>[,<len>] | @<start>-<end>
     * ����Ҫ���ڲ����Դ�ļ����ݶ�.
     * Ĭ�ϲ��������ļ�.

����ģʽ
 * calc <expression>
    �����������ʽ
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