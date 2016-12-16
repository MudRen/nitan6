// This program is a part of NT MudLIB

/*
���ƣ�
        valid_save_binary - ����һ������Ƿ���Դ�����������ĳ�ʽ��
�﷨��
        int valid_save_binary( string file );

        ���� valid_save_binary( �ִ� file );
�÷���
        ֻ������ BINARIES ʱ��Ч��

        ������ʽ����ʱ����������� ALWAYS_SAVE_BINARIES������һ�������ʹ
        ���� #pragma save_binary���ͻ��Գ�ʽ�ĵ���������Ϊ��������
        valid_save_binary����� valid_save_binary ���� 1���˳�ʽ�ᴢ�浽Ӳ
        �����Լӿ����������ʱ�䡣��֮�򲻴��棬�´���������ʱ����ͬ����һ
        �����±���һ�Ρ�
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_save_binary: controls whether an object can save a binary
//   image of itself to the specified "save binaries directory"
//   (see config file)
int valid_save_binary(string filename)
{
        return 1;
}