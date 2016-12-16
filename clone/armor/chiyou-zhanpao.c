

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIR "蚩尤战袍" NOR, ({ "chiyou zhanpao", "chiyou", "zhanpao" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR "一件外型奇异的长袍，上面绘制着魔神蚩尤的标志。\n" NOR);
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 600);
                set("armor_prop/str", 5);
                set("armor_prop/con", 5);
                set("limit", ([
                        "exp"  :  3000000,
                        "int"  :  35,
                        "dex"  :  55,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
