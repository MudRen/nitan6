inherit ROOM;

void create()
{
        set("short", "��ѻ��");
        set("long", @LONG
����һ�����ļ��룬����������һ���������������ƶ��ȽȽ��
����ɽ�����������Ϯ��������ֻ��ѻ�������Ƽʣ��ڰ׷�����ε��
��ۡ�
LONG );
        set("objects", ([
                "/clone/quarry/niao3" : 3,
        ]));
        set("exits", ([
                "northdown": __DIR__"langmeiyuan",
                "southup"  : __DIR__"sanlaofeng",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -350);
        set("coor/y", -330);
        set("coor/z", 110);
        setup();
        replace_program(ROOM);
}