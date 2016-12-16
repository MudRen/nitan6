// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_COAGENT;

#include "fawang.h"
void create()
{
        set_name("������", ({"yin tianzheng", "yin", "tianzheng", }));
        set("long",
        "����һλ���Ŀ����ͺ���ߣ�����һ����ɫ���ۡ�\n"
        "����üʤѩ�������۽ǣ����ӹ���������ӥ�졣\n"
        );

        set("title",HIG "����" HIW "��üӥ��" NOR);
        set("level",9);
        set("gender", "����");
        set("attitude", "peaceful");

        set("age", 72);
        set("shen_type", 1);
        set("per", 22);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3500);
        set("max_qi", 3500);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 900000);
        set("score", 1000000);

        set_skill("force", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("sword", 180);
        set_skill("finger",180);
        set_skill("cuff", 180);
        set_skill("strike", 180);
        set_skill("claw", 220);
        set_skill("literate", 120);

        set_skill("shenghuo-xinfa", 180);
        set_skill("shenghuo-bu", 180);
        set_skill("shenghuo-quan", 180);
        set_skill("guangming-zhang", 180);
        set_skill("liehuo-jian", 180);
        set_skill("sougu-yingzhua", 220);
        set_skill("yinfeng-dao", 220);
        set_skill("tougu-zhen", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("claw", "sougu-yingzhua");
            map_skill("parry", "yinfeng-dao");
            map_skill("finger", "tougu-zhen");
        map_skill("cuff", "pili-quan");
            map_skill("strike", "yinfeng-dao");

        prepare_skill("strike", "yinfeng-dao");
        prepare_skill("finger", "tougu-zhen");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.jue") :),
                (: command("perform finger.feng") :),
        }) );
        create_family("����", 35, "��������");
        set("inherit_title",HIG"����"NOR"����ɢ��"NOR);
        set("master_ob",3);

        set_temp("apply/attack", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 150);

        set("coagents", ({
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "zhang wuji" ]),
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "fan yao" ]),
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "weiyi xiao" ]),
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "yang xiao" ]),
        }));
        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {

        case "��Ѫצ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sougu-yingzhua/xue",
                           "name"    : "��Ѫצ",
                           "sk1"     : "sougu-yingzhua",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        case "��ɱ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tougu-zhen/feng",
                           "name"    : "��ɱ",
                           "sk1"     : "tougu-zhen",
                           "lv1"     : 100,
                           "force"   : 260,
                           "neili"   : 2400,
                           "gongxian": 750,
                           "shen"    : 68000, ]));
                break;

        case "��ɱ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinfeng-dao/jue",
                           "name"    : "��ɱ",
                           "sk1"     : "yinfeng-dao",
                           "lv1"     : 140,
                           "force"   : 260,
                           "neili"   : 2400,
                           "gongxian": 750,
                           "shen"    : 68000, ]));
                break;

        default:
                return 0;
        }
}
