// This program is a part of NT MudLIB
// pang.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_QUESTER;

mixed  ask_back();

void create()
{
        set_name("��ͷ��", ({ "pang toutuo", "pang" ,"toutuo"}));
        set("title", HIY"������"NOR"�󻤷�");
        set("nickname",HIR "�ɶ�������" NOR);
        set("long", "��ͷ��������ߣ������ݵó��棻����Ƥ����ͷ��˫\n"
                    "Ŀ���ݣ�������罩ʬһ�㡣\n" );
        set("gender", "����");
        set("age", 44);

        set("str", 32);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 4700);
        set("qi", 4700);
        set("max_jing", 2400);
        set("jing", 2400);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 60);
        set("level", 20);
        set("combat_exp", 750000);
        set("no_get", "������������������˰ᵽ����ȥ��\n");
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 160);
        set_skill("hand", 160);
        set_skill("strike", 160);
        set_skill("staff", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("yixing-bufa", 160);
        set_skill("shenlong-bashi", 160);
        set_skill("huagu-mianzhang", 160);
        set_skill("shenlong-xinfa", 160);
        set_skill("shedao-qigong", 160);

        map_skill("staff", "shedao-qigong");
        map_skill("force", "shenlong-xinfa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("dodge", "yixing-bufa");

        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "hand.xian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 200);

        create_family("������", 0, "��ɢ����");

        set("inquiry", ([
                "������" : "һ�������벻���������̵�(join shenlongjiao).\n",
                "���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
                "�鰲ͨ" : "����Ƣ�����ã�Ҫ�������Ĳźá�\n",
                "����"   : "����Ƣ�����ã�Ҫ�������Ĳźá�\n",
                "�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
                "������" : (: ask_back :),
        ]));
        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
        add_money("silver", 10);
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "������" )
        {
                message_vision("$N�Թ��ԵĶĲ�������û������$n��˵ʲô��\n",
                               this_object(), me);
                return -1;
        }

        message_vision("$N��Ȼ̧��ͷ�����������´�����һ��"
                       "��$n���۽�΢΢һ����\n�������е��ž�"
                       "�������������������\n˵�գ�$N��"
                       "��$n����ææ�ĳ�������ȥ��\n", this_object(), me);
        tell_object(me, "�����" + name() + "���������ţ�������"
                    "һ���ص���" + name() + "ָ��ǰ�������һֱ��"
                    "�����ˣ�ȥ�ɣ���\n");
        tell_object(me, HIW "�����˺ܾã�Խ��Խ�䣬��Ȼ��ǰһ����"
                    "���Ѿ����������⣬ֻ��������Ұ��ӳ���ۻ����ҡ�\n" NOR);
        me->move("/d/shenlong/haitan");
        return -1;
}

void attempt_apprentice(object ob)
{
        command("say �����������������ʦȥ�ҽ����ɡ�");
}

void init()
{
        add_action("do_join", "join");
}

int do_join(string arg)
{
        if (arg != "shenlongjiao")
                return notify_fail("��Ҫ����ʲô��֯��\n");

        message_vision("$N���˰��֣���$n�������ҿɲ���������̣��㻹��ȥ"
                       "������������ȥ�����ǽ������ˡ�\n",
                       this_object(), this_player());
        return 1;
}

/*
void unconcious()
{
        die();
}

*/