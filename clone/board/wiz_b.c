// /clone/board/wiz_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("��ʦ���Բ�", ({ "board" }) );
        set("location", "/d/wizard/wizard_room");
        set("board_id", "wiz_b");
        set("long", "����һ��ר����ʦʹ�õ����԰塣\n" );
        set("poster_level", 1);
        set("wizard_only", 1);
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
