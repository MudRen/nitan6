// Room: /d/yanping/xishan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "��ɽ");
        set("long", @LONG
��ɽ�����ڸ������룬ɽ��������ѧ����ɽ������һ��ͤ��ͤ��
��������������ѧ��������ɽ�����͡���ͤ���ǡ��Ͻ����ؽ���ѧ��
���� (bei)�����ļ����˵�ɽ����ʤ�����·���֮ʢ�£�׷������
�п����ޡ�
LONG );
        set("exits", ([
                "northup"   : __DIR__"zhouxue",
                "southdown" : __DIR__"road3",
        ]));
        set("item_desc", ([
                "bei" :
"
���ɺ�ҳ�ҵ�ɣ�Բ�ף�׭��������������ߣ������ҹ�������
��ʿ����Զ׫�ģ���ʿ�޼����顣

                    �Ͻ����ؽ���ѧ��

    ��ƽ���Σ�������֮�塣����ѧ����ɽ���ؾ���ʤ��������˫
캡����ɡ��ı��������Ħ�ƣ������������ϡ���������ˮ���
������������ԣ������Խ��̶���쿪�����Ϲ�����ţ���䡣��ʱ
ΰ�˱��������Ρ�ƣ������ˣ���ҵ����ʦ����ѭ���������Զ��
������������������Ҳ��......
"
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}