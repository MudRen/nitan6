// smith.c

inherit SMITH;

void create()
{
        set_name("����", ({ "tie jiang", "smith" }));
        set("title", "�������ϰ�");
        set("shen_type", 1);

        set("gender", "����" );
        set("age", 33);
        set("long", "����������ǯ��סһ����ȵ�����Ž�¯�С�\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/d/city/obj/changjian",
                "/d/city/obj/hammer",
                "/d/beijing/obj/tudao",
                "/d/city/obj/dagger",
                "/d/xingxiu/obj/tiegun",
                "/d/city/obj/gangdao",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}
