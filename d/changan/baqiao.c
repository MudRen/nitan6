//  Room:  /d/changan/baqiao.c

inherit  ROOM;

void  create  ()
{
        set("short",  "���");
        set("long",  @LONG
����ֽа��ţ�����ˮ����ʼ����������ϡ������湫�����ϡ�
ָ�ľ�����������ͿͶൽ��ţ���������������Ȼ�����ֳơ���
���š�������֮���������ʹ�������ѩ���纮��ɳ��ʯ¶���˳ơ����
��ѩ������Ϊ�����а˾���֮һ��
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" :  __DIR__"dong-chengmen",
                "east" :  __DIR__"road4",
        ]));
        set("outdoors", "guanzhong");
        set("no_clean_up", 0);
        set("coor/x", -10660);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}