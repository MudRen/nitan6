// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹�ƽ��");
        set("long", @LONG
�����߹ȵ�һ����ƽ̹�����ĵش����������ǰ�С��Ҷ�����մ�
����С����ʯ��ƽ���ĵ��ƴ�������������Ϊ���죬�����������
�߲�����ľ��
LONG );

        set("exits", ([ 
            "southeast" : __DIR__"shegu5",
            "west"      : __DIR__"shegu7",
            "northeast" : __DIR__"shegu13",
        ]));

        set("objects", ([
             __DIR__"obj/stone" : 1,
        ]));

        set("resource/grass", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49990);
        set("coor/y", 20160);
        set("coor/z", 20);
        setup();
}