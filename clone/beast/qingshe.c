#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(NOR + GRN "竹叶青蛇" NOR, ({ "qing she", "qing", "she" }));
        set("long", GRN "这是一只让人看了起鸡皮疙瘩的竹叶青蛇。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 40);
        set("max_qi", 400);
        set("max_ging", 400);
        set("combat_exp", 6000);

        set("snake_poison", ([
                "level"  : 45,
                "perhit" : 25,
                "remain" : 45,
                "maximum": 45,
                "supply" : 2,
        ]));

        set("power", 10);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 90);
        set_temp("apply/defense", 90);
        set_temp("apply/unarmed_damage", 40);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she" && arg!="qing she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");
        return notify_fail("竹叶青过于细小，不能化为杖。\n");
}