// This program is a part of NT MudLIB
// person used in quest
// update by Lonely

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

#define GIFT_DIR        "/clone/gift/"
string  *GF_LIST = ({
        "xiandan", "shenliwan", "unknowdan", "xisuidan",
});

int  accept_object(object who, object ob);
int do_nod(string arg);
void random_move();
int  leave();
int  is_stay_in_room()  { return 1; }

void create()
{
        ::create();
        set("gender", "����");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);
        set("auto_perform", 2);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
        set_temp("dest_time", 1200 + time());

        add_money("silver", 10 + random(20));

        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_nod", "nod");
}

void set_from_me(object me, int scale)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me) - 2);
        my = query_entire_dbase();

        if (my["max_qi"] > 60000)
                my["max_qi"] = 60000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 30000)
                my["max_jing"] = 30000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        my["quest_count"]=query("quest_count", me);

        // �����޸�
        exp=query("combat_exp", me)*12/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);


        if (my["combat_exp"] > 200000 && random(100) < 5)
        {
                // ���� > 200K��5%���ʳ��ֶ������
                set_temp("multi-enemy", 1);
        }


        my["jiali"] = query_skill("force") / 3;
        if (query("place") == "����")
                set_temp("dest_time", 900 + time());
        else
                set_temp("dest_time", 600 + time());
}

int do_nod(string arg)
{
        object obj;
        object me = this_player();
        object ob = this_object();
        int amount;

        if( !arg || arg != query("id", ob) || 
            !query_temp("family_quest/waiting", me) )
                return 0;

        me->command("nod");

        if( query_temp("family_quest/ob", me) )
        {
                message_sort(HIW "ֻ��$N" HIW "��Ц����������������ʶʱ����Ϊ���ܣ�" +
                        RANK_D->query_respect(me) + "��Ȼ�������ˣ��ٺ٣��������ɵ�" +
                        "�͹����ˣ���������\n\n" NOR,
                        ob, me);
                obj = new(GIFT_DIR + GF_LIST[random(sizeof(GF_LIST))]);

                tell_object(me, HIR + ob->name() + "�ݸ�����" + obj->name() +
                        HIR "�Ժ��³�һ����Ѫ���ﳤ��ȥ��\n" NOR);
                if (! obj->move(me))
                        obj->move(environment(me));
                delete_temp("family_quest", me);
                destruct(ob);
                return 1;
        }
        amount=query_temp("family_quest/waiting", me);

        message_sort(HIW "ֻ��$N" HIW "��Ц����������������ʶʱ����Ϊ���ܣ�" +
                RANK_D->query_respect(me) + "��Ȼ�������ˣ��ٺ٣�������" +
                chinese_number(amount) + "���ƽ�͹����ˣ���������\n\n" NOR,
                ob, me);
        MONEY_D->pay_player(me, amount * 10000);
        tell_object(me, HIR + ob->name() + "�ݸ�����" + chinese_number(amount) +
                "���ƽ��Ժ��³�һ����Ѫ���ﳤ��ȥ��\n" NOR );
        delete_temp("family_quest", me);
        destruct(ob);
        return 1;
}

void kill_ob(object ob)
{
        int lvl;

        if (! is_busy())
                exert_function("powerup");

        if( query("quest/id", ob) != query("id") )
        {
                ::kill_ob(ob);
                return;
        }

        if (lvl = query_temp("multi-enemy"))
        {
                // ���ֶ������
                delete_temp("multi-enemy");
                call_out("do_help_me", 1 + random(2), ob);
        }
        ::kill_ob(ob);
}

void do_help_me(object ob)
{
        if (! objectp(ob) || environment(ob) != environment())
                return;

        switch (random(3))
        {
        case 0:
                message_vision(HIW "\n$N" HIW "�����ȵ�������һ��" +
                               ob->name(1) +
                               HIW "����λ����Ҫ�ٵ��ˣ��������" +
                               RANK_D->query_self(this_object()) +
                               "һ�ѣ���\n" NOR, this_object(), ob);
                break;

        case 1:
                message_vision(HIW "\n$N" HIW "��Ȼ���വ"
                               "�ڣ������˲���΢΢һ㶡�\n" NOR,
                               this_object());
                break;

        case 2:
                message_vision(HIW "\n$N" HIW "һ����Х������"
                               "�಴������ԶԶ�Ĵ��˿�ȥ��\n" NOR,
                               this_object());
                break;
        }

        call_out("do_continue_help", 1 + random(4), ob);
}

void do_continue_help(object ob)
{
        int n;
        object *obs;

        if (! objectp(ob) || environment(ob) != environment())
                return;

        n = random(3) + 1;
        set_temp("quest/help_count", n, ob);
        message("vision", HIR "˵ʱ�٣���ʱ�죡ͻȻת��" +
                          chinese_number(n) +
                          "���ˣ�һ�����ǰ������������"
                          "�з�����\n" NOR, environment());

        // ���ɰ���
        obs = allocate(n);
        while (n--)
        {
                obs[n] = new(CLASS_D("generate") + "/killed.c");
                NPC_D->set_from_me(obs[n], ob, 200);
                delete_temp("multi-enemy", obs[n]);
                set_temp("help_who", this_object(), obs[n]);
                set_temp("is_helper", 1, obs[n]);
        }

        // ����ս��
        set_temp("help_ob", obs);
        set_temp("help_count", sizeof(obs));
        obs->move(environment());
        obs->set_leader(this_object());
        obs->kill_ob(ob);
}

int filter_to_bonus(object ob, object aob)
{
        object *obs;

        if (! playerp(ob) || ! living(ob) ||
            ! ob->is_killing(query("id")))
                // ��������Ҳ��Ҳ�����ɱ��(NPC)
                return 0;

        // Э���Ķ���һ��
        if( aob == query_temp("quest/assist", ob) )
                return 1;

        // ����һ������
        obs = ob->query_array_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;

        // ����һ��������
        obs = ob->query_team_member();
        if (sizeof(obs) > 0 && member_array(aob, obs) != -1)
                return 1;
}

// remove
void remove()
{
        object qob;

        if (objectp(qob = query_temp("quest_ob")))
        {
                // ������Ѿ���ʧ�ˣ�ȡ�������������
                destruct(qob);
        }

        ::remove();
}

// �漴���·���
void random_place(string msg)
{
        object old_env;
        object qob;
        string *not_place;
        string new_place;
        int limit;
        int qcount;

        // ���ԭ�ȴ��������񣬾�ֱ���޸���Ϣ
        if (objectp(qob = query_temp("quest_ob")))
                set("introduce", msg, qob);
        else
                qob = new("/clone/quest/avoid");

        // �漴ѡ������һ���ط�����NPC
        old_env = environment();
        not_place = ({ query("place") });

        if (query("combat_exp") < 500000)
                not_place += ({ "����һ��" });

        if (query("combat_exp") < 800000)
                not_place += ({ "����" });

        NPC_D->place_npc(this_object(), not_place);

        // ���ݸ�ʽ����Ϣ���ɽ��
        msg = replace_string(msg, "$N", name(1));

        qcount = query("quest_count");
        if ((qcount < 100 || qcount >= 900) && random(10) ||
            (qcount >= 100 && qcount < 900) && random(50))
        {
                new_place = query("place");
                if (new_place == "����")
                        limit = 1800;
                else
                        limit = 1200;
        } else
        {
                new_place = "��Զ�ĵط�";
                limit = 1800;

                // ���ٴ����ļ۸�
                set("ask_cheap", 3);
        }
        set_temp("dest_time", limit + time());
        msg = replace_string(msg, "PLACE",  new_place);

        // ��ʼ������¼�������
        set("introduce", msg, qob);
        qob->init_quest(name(1), old_env);
        set_temp("quest_ob", qob);

        return;
}

// �ε���ʱ���л�������
void unconcious()
{
        object *obs;
        object ob;
        object me;
        int amount = 10 + random(10);
        mapping my;
        string msg;
        string quester;
        string *condition = ({
                "������������Ҫ��֧", "ͷ�ؽ��ᣬ���Ͼ͵�",
                "ŻѪ��������ð����", "�˺����ۣ������м�",
        });

        if (! query_temp("is_helper") && ! query_temp("help_ob"))
        {
                if (random(100) < 8)
                {
                        // 10%��������
                        switch (random(8))
                        {
                        case 0:
                                msg = HIC "$N" HIC "���һ�������¼�"
                                      "����Ѫ���ۿ����Ѳ�֧����Ȼһ"
                                      "����Ӱ�ܳ��������������У���"
                                      "��$n" HIC "��ֻ����ôһ˲�䣬"
                                      "�����Ѿ�����$N" HIC "�����Ӷ�"
                                      "�ߣ���Ȼδ�����ۼ���\n" NOR;
                                break;
                        case 1:
                                msg = HIC "$N" HIC "ҡҡ��׹���ۿ���"
                                      "Ҫ��������Ȼ�������һ����Ѫ"
                                      "��$n" HIC "��æ����һ�ܣ�����"
                                      "��ʱ��$N" HIC "��Ȼ��������"
                                      "����һ�ݣ���ȻƮ��ʮ����֮Զ"
                                      "������Ŀ�ɿڴ���ֻ��$N" HIC
                                      "ɲ�����һ����Ӱ��������ʧ��"
                                      "\n" NOR;
                                break;
                        case 2:
                                msg = HIC "��$n" HIC "һ���֮�£�"
                                      "$N" HIC "ֻ���м�֮�������ﻹ"
                                      "�л���֮�����ۿ���Ҫ��ɥ$n" HIC
                                      "֮�֣�$N" HIC "��Ȼ��ʽһ�䣬"
                                      "�����޷����������Ϻ�����$n" HIC
                                      "��һ�����ѱ�$N" HIC "������"
                                      "�б��ˣ�ֻ��$N" HIC "������"
                                      "���Ӷݶ��ߡ�\n" NOR;
                                break;
                        case 3:
                                msg = HIC "ֻ��$N" HIC "����һ����"
                                      "����ɫ��΢����һЩ����Ȼ�ŷ�"
                                      "�����춯�ص�һ�����ֱ���"
                                      "$n" HIC "��������������һ��"
                                      "��$N" HIC "����һת��ƮȻ��"
                                      "ȥ������$n" HIC "���ֲ�����"
                                      "׷�ϲ��ϣ�\n" NOR;
                                break;
                        case 4:
                                msg = HIC "$n" HIC "�����������ۿ�"
                                      "��Ҫ���֣��������У���$N" HIC
                                      "���Ǳ��޿ɱܣ����޿��ˣ�$N"
                                      HIC "��ɫ��ɫ�ֻʣ����м��͵�"
                                      "ҧ����⣬���ۡ����³���$n"
                                      HIC "ֻ����ǰһ�������������"
                                      "ɢȥ�����ﻹ��$N" HIC "��Ӱ"
                                      "�ӣ�\n" NOR;
                                break;
                        case 5:
                                msg = HIC "$N" HIC "����һ����ȴ��"
                                      "��С�������������У�һ����"
                                      "�������ѵ�����$n" HIC "��״"
                                      "����ǰȥ����Ȼ��ǰ�ǹ�����"
                                      "���ֻ��¼��ˣ�ֻ�����˹���"
                                      "��Ц������$N" HIC "Ī�ţ���"
                                      "��Ҳ����˵������һ���֣���"
                                      "ʮ������ɳ�������$n" HIC
                                      "�ֵ����£����������$N" HIC
                                      "��ȥ�ˡ�\n" NOR;
                                break;
                        case 6:
                                msg = HIC "$N" HIC "�������£���Ȼ"
                                      "������$n" HIC "��ס��ʽ��Ц��"
                                      "����$N" HIC "���㡭��������δ"
                                      "�䣬����$N" HIC "��Ĵ���һ"
                                      "��ֱ��$n" HIC "��Ҫ����$n" HIC
                                      "���һ������æ�мܣ�ֻ������"
                                      "Ϣ���ң�����Ż�£�$N" HIC "Ҳ"
                                      "��׷����ֻ�Ǽ������ߣ�$n" HIC
                                      "���˼�������ȥ����ǰ���ƣ�ȴ"
                                      "�Ѳ���$N" HIC "����Ӱ��\n" NOR;
                                break;
                        default:
                                msg = HIC "$N�������ˣ���Ȼ���У���"
                                      "�߼�ֻ����������һʱ���$n"
                                      HIC "�������ƣ������ٻ���$N"
                                      HIC "��Ȼ�����л��ɳˣ������"
                                      "�Ź����������У�ɱ��һ��Ѫ·"
                                      "���ʹ˲�����\n" NOR;
                                break;
                        }

                        clean_up_enemy();
                        obs = query_enemy();
                        if (sizeof(obs) > 0) ob = obs[0]; else ob = 0;
                        if (! objectp(ob))
                                msg = replace_string(msg, "$n", "����");
                        message_sort("\n" + msg, this_object(), ob);

                        // ���NPC���ж�״̬
                        clear_condition(0);

                        // �ָ�NPC������
                        my = query_entire_dbase();
                        my["eff_jing"] = my["max_jing"];
                        my["jing"]     = my["max_jing"];
                        my["eff_qi"]   = my["max_qi"] * 2 / 3;
                        my["qi"]       = my["eff_qi"];
                        my["neili"]    = my["max_neili"] * 2;
                        if (! intp(query_temp("escape_times")))
                                set_temp("escape_times", 1);
                        else
                                addn_temp("escape_times", 1);

                        // �Ǽ�һ�������Ա���ҿ���׷�������м�
                        switch (random(9))
                        {
                        case 0:
                                msg = "��˵$N���˴������ߣ���˵�Ƕ㵽PLACEȥ�ˡ�";
                                break;
                        case 1:
                                msg = "��˵$N���˶��֣���㱻������������"
                                      "���ǽ��������ˣ�����ȥ��PLACE��";
                                break;
                        case 2:
                                msg = "��˵��$N����һ��Ѫս�������ȫ��"
                                      "���ˣ�������ȥ��PLACE�ɡ�";
                                break;
                        case 3:
                                msg = "$N��˵����PLACE��������ǰһ�������������ġ�";
                                break;
                        case 4:
                                msg = "��˵$N���˴����˰ɣ��ף���������˵"
                                      "��PLACEҲ������ѽ��";
                                break;
                        case 5:
                                msg = "������Ҳ��̫�����������˵��������PLACE��";
                                break;
                        case 6:
                                msg = "��������ɶ����������PLACEô��";
                                break;
                        case 7:
                                msg = "ǰ��������������������أ�����Ӧ��"
                                      "��ȥ��PLACE�ɡ�";
                        default:
                                msg = "$Nѽ������˵��PLACE�������������������ˡ�";
                                break;
                        }

                        random_place(msg);
                        remove_all_enemy(1);
                        return;
                } else
                if (objectp(me = query_last_damage_from()) &&
                    environment() == environment(me) &&
                    !query_temp("family_quest/waiting", me) )
                {
                        switch (random(20))
                        {
                        case 1:
                                message_sort(HIR "\n�ۼ�$N" HIR + condition[random(sizeof(condition))] +
                                        "��ͻȻ$N���һ�������˼�����\n����ͨ����$n����������"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "ͻȻ�ӻ����ͳ�һ�Ѱ׻��������ӣ�С��"
                                        "�����������λ" + RANK_D->query_respect(me) + "��\n��"
                                        "������һ�棨nod����Σ���" + chinese_number(amount) +
                                        "���ƽ�͹����ˣ���\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());
                                set_temp("family_quest/waiting", amount, me);
                                return;
                        case 2:
                                message_sort(HIR "�ۼ�$N" HIR + condition[random(sizeof(condition))] +
                                        "��ͻȻ$N���һ�������˼�����\n����ͨ����$n����������"
                                        "\n" NOR, this_object(), me);
                                tell_object(me, HIW + this_object()->name() + "ͻȻ�ӻ����ͳ�һ���ɵ���С��"
                                        "�����������λ" + RANK_D->query_respect(me) + "��\n��"
                                        "������һ�棨nod����Σ����ɵ��͹����ˣ���\n" NOR);
                                clean_up_enemy();
                                remove_all_enemy(1);
                                clear_condition(0);
                                set("qi", 1, this_object());
                                set("jing", 1, this_object());

                                set_temp("family_quest/waiting", amount, me);
                                set_temp("family_quest/ob", 1, me);
                                return;
                        default:
                                break;
                        }
                }
        }

        if (stringp(quester = query_temp("quester")))
        {
                // ����ҵ���ȡ��quest����
                if (objectp(ob = find_player(quester)))
                        set_temp("quest/escape_times", query_temp("escape_times"), ob);
        }
        ::unconcious();
}



// �������NPC������ʱ�򣬼���Ƿ���Խ��н���ĳЩ��ҡ�����
// �Ķ��󣺰�������������������������ˣ� ��Ȼ����Ҫ��ɱ��
// ��������������ɶ�����ξ�������������жԸ�NPC����ɱ
// �������Э�������������ߵ���ҡ�
void die(object killer)
{
        mapping quest;          // ����
        object *obs;            // ���������п��Խ�����
        object dob;             // �������NPC����
        object hob;             // Э����
        object aob;             // ��Э����
        int qlevel;             // ��������ĵȼ�
        int lvl;                // NPC�ĵȼ�
        int scale;              // NPC���еİ��ֺ����ܵĴ���
        int n;                  // ���Խ������˵���Ŀ
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
        int weiwang;            // ��Ҫ�Ϸֵ�����
        int score;              // ��Ҫ�Ϸֵ�����
        int extra_exp;          // ���ε��˵Ķ��⾭��
        int extra_pot;          // ���ε��˵Ķ���Ǳ��
        string quester;         // ��Ҫ��������������ID
        object qob;             // ��Ҫ�������������Ҷ���
        object ob;              // NPC��������Ʒ
        string *ob_list = ({    // ������NPC���ϵı��������Ʒ
                "/clone/gift/puti-zi",
                "/clone/gift/jiuzhuan",
                "/clone/gift/tianxiang",
                "/clone/gift/xuanhuang",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/str3",
                "/clone/fam/item/stone1",
                "/clone/fam/item/stone2",
                "/clone/fam/item/stone3",
                "/clone/fam/item/stone4",
                "/clone/fam/etc/lv5f",
                "/clone/fam/etc/lv5d",
                "/clone/fam/etc/lv7c",
                "/clone/fam/etc/lv7d",
                "/clone/fam/etc/lv7b",
                "/clone/fam/etc/lv7a",
                "/clone/fam/etc/prize5",
                "/clone/fam/item/baxian",
                "/clone/fam/item/kunlun",
                "/clone/fam/item/leihuo",
                "/clone/fam/item/lihuo",
                "/clone/fam/item/zhenlong",
                "/clone/tessera/rune16", 
                "/clone/tessera/rune17", 
                "/clone/tessera/rune18", 
                "/clone/tessera/rune19", 
                "/clone/tessera/rune20", 
        });

        // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if( objectp(dob) && query_temp("owner", dob) )
                dob=query_temp("owner", dob);

        while (1)
        {
                // ��¼���������Ѿ���ֹ
                if (stringp(quester = query_temp("quester")))
                {
                        qob = UPDATE_D->global_find_player(quester);
                        if( query("quest/id", qob) == query("id") )
                                set("quest/notice", "die", qob);
                        UPDATE_D->global_destruct_player(qob, 1);
                }

                if( dob && query("quest/id", dob) == query("id") )
                        // ���Լ�������
                        break;

                if( dob)aob=query_temp("quest/assist", dob);
                if( aob && query("quest/id", aob) == query("id") )
                        // ��Э������ɱ����
                        break;

                if (dob && dob->in_array() && dob->query_array_status())
                        // ������ɱ����
                        break;

                if (dob && dob->in_team())
                        // �����ɱ����
                        break;

                // �����������߻�������������Э������ɱ�������¼֮��
                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s����ɱ���ˡ�", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) died at %s because %s.\n",
                                                      log_time(), name(), query("id"),
                                                      environment()->short(),
                                                      dob?sprintf("%s(%s)",dob->name(1),query("id", dob)):"none"));
                */

                break;
        }

        if (! aob) aob = dob;

        if (! aob)
        {
                // û���ҵ� QUEST ������
                ::die(killer);
                return;
        }

        // �쿴Ŀǰ����ɱ�ҵ��ˣ��Ƿ�Ҳ��ֵ�ý�����
        obs = all_inventory(environment(this_object()));
        obs = filter_array(obs, (: filter_to_bonus :), aob);

        if ((n = sizeof(obs)) > 0)
        {
                // ���Ҵ����ҵ��ˣ�����ɱ���ҵ���
                dob = query_defeated_by();

                // ���������أ��ܹ����������е��˷֣����ÿ
                // �˼���һ������������д�������˵���һ�
                // �ö����һЩ������
                lvl = NPC_D->check_level(this_object());
                exp = 15 + random(10) + lvl;
                pot = 9 + random(5) + lvl;
                weiwang = 8 + random(6) + lvl / 2;
                score = 9 + random(6) + lvl / 2;

                // �����������ĵȼ����н�������
                switch(query("quest/level", aob) )
                {
                case 1:
                        break;
                case 2:
                        exp += exp / 2;
                        pot += pot / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        break;
                case 3:
                        exp += exp;
                        pot += pot;
                        weiwang += weiwang;
                        score += score;
                        break;
                default:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        weiwang = weiwang / 2 + 1;
                        score = score / 2 + 1;
                        break;
                }
                // ���NPC�����˰��֣�����Ի�ö��⾭��
                if ((scale = sizeof(query_temp("help_count") +
                     query_temp("escape_times") * 2)) > 0)
                {
                        exp += exp * scale / 2;
                        pot += pot * scale / 2;
                }
                // �����˾��־��飺Ϊʲô����n + 2��������Ϊ
                // �����ҵ��˷����ݾ��飬������n + 1���ټ���
                // ��������������1����ô����n + 2��
                if (n > 1)
                {
                        exp *= 1.2;
                        pot *= 1.2;
                        weiwang *= 1.2;
                        score *= 1.2;
                }
                exp = exp / (n + 2) + 1;
                pot = pot / (n + 2) + 1;
                weiwang = weiwang / (n + 2) + 1;
                score = score / (n + 2) + 1;

                // ��������ҵĶ��⽱��
                if (objectp(dob) && member_array(dob, obs) != -1)
                {
                        extra_exp = 1 + random(exp);
                        extra_pot = 1 + random(pot);
                        if( query("combat_exp", dob)<query("combat_exp")/2 )
                        {
                                // ���ֵ����书�Ƚϵͣ���õĶ��⽱����
                                extra_exp *= 2;
                                extra_pot *= 2;
                        } else
                        if( query("combat_exp", dob)>query("combat_exp")*2 )
                        {
                                // ���ֵ����书̫�ߣ���õĶ��⽱����
                                extra_exp /= 2;
                                extra_pot /= 2;
                        }
                }

                // ���н���
                foreach (hob in obs)
                {
                        // �����ӳٽ�����Ϊʲô��ô���ã��ܼ򵥣�
                        // ��Ϊ��ϣ������ڿ���NPC�����Ժ���ܹ�
                        // ����������
                        GIFT_D->delay_bonus(hob, ([ "exp"     : exp + random(4) +
                                                    ((hob == dob) ? extra_exp : 0),
                                                    "pot"     : pot + random(3) +
                                                    ((hob == dob) ? extra_pot : 0),
                                                    "weiwang" : weiwang + random(3),
                                                    "score"   : score + random(3),
                                                    "prompt"  : "����" + name() + "֮��" ]));
                }
        }

        // �������������ɵ��������������������Ʒ
        if ((query_temp("is_helper") || query_temp("help_ob") ||
            query_temp("escape_times")))
        {
                // �а��֡����֡��������ܹ���NPC�оųɵĻ�����Ʒ��������
                ob = new(ob_list[random(sizeof(ob_list))]);
                message_vision(HIY"$N"HIY"����һ�ˣ�����һ"+query("unit", ob)+
                        ob->name() + HIY "��\n\n" NOR, this_object());
                ob->move(environment());
        }

        /*
        // ����Ҫ�������������ң������޷�����Զ������
        // ��ô����������
        // ��������Լ�ɱ���ģ�����������Զ������
        if (! qob || random(20) ||
            quester != query("id", dob) || 
            ! mapp(quest = QUEST_D->prepare_quest(qob)))
        {
                ::die(killer);
                return;
        }

        // �����������
        set("quest/finished", 1, qob);

        // ʹ�����ŷ�������
        QUEST_D->remote_assign_quest(qob, quest);
        */

        // ��������
        ::die(killer);

        return ;
}

int accept_fight(object ob)
{
        command("say �ã����ǾͱȻ��Ȼ���");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say ����ȥ�ɣ�");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say �ߣ�������");
        return 1;
}

void random_move()
{
        if (query_temp("is_helper"))
        {
                // is a helper
                if (! environment())
                {
                        // not in environment? unavaliable npc.
                        destruct(this_object());
                        return;
                }

                if (! query_temp("help_who"))
                {
                        // owner is killed. destruct this helper
                        if (! living(this_object()))
                                message_vision("$N���������˹�����\n",
                                               this_object());

                        message_vision("$N�������ܣ����Ҵҵ������ˡ�\n",
                                       this_object());
                        destruct(this_object());
                        return;
                }

                // move with owner
                return;
        }

        if (time() > query_temp("dest_time"))
        {
                message_vision("$N����ææ�����ˡ�\n", this_object());

                /*
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s���ӵ�����ɽ���󣬴Ӵ˲��ٳ�û�����䡣", name()));
                log_file("static/killed_die", sprintf("%s %s(%s) vanished because timeout(%d:%d).\n",
                                                      log_time(), name(), query("id"),
                                                      time() - query_temp("born_time"),
                                                      query_temp("dest_time") - query_temp("born_time")));
                */
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}
