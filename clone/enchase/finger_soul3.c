#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "指套之魂" NOR, ({"finger soul3", "finger", "soul3"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "这是一个指套之魂。\n" NOR);
                set("unit", "个");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "finger");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

