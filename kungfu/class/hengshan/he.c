// Last Modified by Sir on May. 22 2001
// he.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>;
#include "hengshan.h"

void create()
{
        set_name("�Ǻ�", ({ "yi he", "he" }) );
        set("long", "����һλ����Ů�ᣬ������������������ʮ�ֳ���������\n");
        set("gender", "Ů��");
        set("class", "bonze");
        set("age", 35);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 50);
        set("max_qi", 1500);
        set("max_jing", 800);
        set("combat_exp", 500000);
        set("shen_type", 1);

        set_skill("unarmed", 90);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_skill("parry", 90);
        set_skill("dodge", 100);
        set_skill("strike", 90);
        set_skill("hand", 90);
        set_skill("buddhism", 100);
        set_skill("baiyun-xinfa",100);
        set_skill("hengshan-jian", 150);
        set_skill("chuanyun-shou",130);
        set_skill("tianchang-zhang",120);
        set_skill("lingxu-bu", 150);
        set_skill("literate", 50);

        map_skill("force","baiyun-xinfa");
        map_skill("sword", "hengshan-jian");
        map_skill("strike","tianchang-zhang");
        map_skill("hand","chuanyun-shou");
        map_skill("parry", "hengshan-jian");
        map_skill("dodge", "lingxu-bu");
        prepare_skill("strike", "tianchang-zhang");
        prepare_skill("hand", "chuanyun-shou");
        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yuyin" :),
                (: perform_action, "sword.liuyun" :),
                (: perform_action, "strike.diezhang" :),
                (: perform_action, "hand.break" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        create_family("��ɽ��", 14, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)>10000 && query("family/family_name", ob) != "��ɽ��" )
        {
                command("say �Һ�ɽ��ע�����ޣ��Ե���Ҫ�������ܼ�į��");
                command("say �ڽ����������棬" + RANK_D->query_respect(ob) +
                        "�����ḻ���Ƿ����ں�ɽ�޵���");
                return;
        }
        if( query("shen", ob)<0 )
        {
                command("say �Һ�ɽ����������������֮һ���Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }
        if( query("gender", ob) != "Ů��" )
        {
                command("say �Һ�ɽֻ��Ůͽ��");
                return;
        }
        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit "+query("id", ob));
}