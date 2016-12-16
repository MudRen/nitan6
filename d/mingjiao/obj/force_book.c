// force_book.c 内功心法

inherit ITEM;

void create()
{
        set_name("太极拳经", ({ "shu", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", 
"这是一本手抄本，是张教主荣登教主之位时张真人所赠。\n"
"里面密密麻麻的画了不少打坐吐呐的姿势。\n"
                );                                
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":        "force",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        30,        // jing cost every time study this
                        "difficulty":        10,        // the base int to learn this skill
                        "max_skill":        50        // the maximum level you can learn
                ]) );
        }
}