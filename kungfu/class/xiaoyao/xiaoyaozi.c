// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#define ZHIHUAN    "/clone/unique/zhihuan"

mixed ask_zhihuan();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();

void create()
{
        object ob;
        set_name("逍遥子", ({ "xiaoyao zi", "xiaoyao", "zi" }));
        set("title", "逍遥派开山祖师");
        set("long", @LONG
眼前此人须眉皆白，看不出有多老。他便是逍
遥派开山祖师无崖子。然而似乎身染重疾，行
动不便。虽然如此，从眉宇仍然看得出此人当
年必然是一位风流倜傥的美男子。想不到今天
沦落到这个地步，真是世事难料。
LONG );
        set("gender", "男性");
        set("age", 95);
        set("class", "scholar");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 36);
        set("int", 41);
        set("con", 37);
        set("dex", 38);

        set("max_qi", 7500);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("level", 50);
        set("combat_exp", 5000000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("beiming-shengong", 600);
        set_skill("dodge", 600);
        set_skill("lingbo-weibu", 600);
        set_skill("feiyan-zoubi", 600);
        set_skill("strike", 600);
        // set_skill("panyang-zhang", 440);
        set_skill("liuyang-zhang", 600);
        set_skill("hand", 600);
        set_skill("qingyun-shou", 600);
        set_skill("zhemei-shou", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("liuyue-jian", 600);
        set_skill("blade", 600);
        set_skill("ruyi-dao", 600);
        set_skill("literate", 800);
        set_skill("medical", 650);
        set_skill("xiaoyao-qixue", 600);
        set_skill("mathematics", 800);
        set_skill("qimen-wuxing", 800);
        set_skill("drawing",   800);
        set_skill("chuixiao-jifa", 600);
        set_skill("tanqin-jifa", 600);
        set_skill("chess", 800);
        set_skill("calligraphy", 800);
        set_skill("construction", 1000);
	set_skill("xiaoyao-you", 800);
        set_skill("martial-cognize", 940);

        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-jian");
        map_skill("sword", "liuyue-jian");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遥派", 1, "开山祖师");
        set("class", "taoist");

        set("inquiry", ([
                "流月剑诀"   : (: ask_skill1 :),
                "天升剑诀"   : (: ask_skill2 :),
                "洛神凌波"   : (: ask_skill3 :),
                "生死符"     : (: ask_skill4 :),
                "寰阳式"     : (: ask_skill5 :),
                "折梅式"     : (: ask_skill6 :),
                "海渊式"     : (: ask_skill7 :),
                "化妖功"     : (: ask_skill8 :),
                "逍遥神仙环" : (: ask_zhihuan :),
                "掌门人信物" : (: ask_zhihuan :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "hand.hua" :),
                (: perform_action, "dodge.ling" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
        setup();

        if (clonep())
        {
                ob = find_object(ZHIHUAN);
                if (! ob) ob = load_object(ZHIHUAN);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wear();
                }
        }

        carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query_temp("pass_zhenlong", ob) )
        {
                int btimes;
                delete_temp("pass_zhenlong", ob);
                if( query("betrayer/times", ob) )
                {
                        command("sigh");
                        command("say 你破了珍珑，和我是有缘人，可是你"
                                "曾经判师，却不能收你。");
                        return;
                }

                command("haha");
                command("say 你破了珍珑，和我是有缘人，我一定要收你为"
                        "徒！");
                btimes=query("betrayer/times", ob);
                command("recruit "+query("id", ob));
                set("betryer/times", btimes, ob);

                if( query("max_neili", ob)<500 )
                {
                        command("say 不过你内力太差…嗯…也好，待我传功于你！");
                        set("max_neili", 500+random(100), ob);
                        if (ob->query_skill("force", 1) < 50)
                                ob->set_skill("force", 50 + random(10));

                        if (ob->query_skill("beiming-shengong", 1) < 50)
                                ob->set_skill("beiming-shengong", 50 + random(10));

                        message_vision(HIC "$N" HIC "把掌心按在$n" HIC "天灵盖上，双眼微"
                                       "闭，手掌不住的颤动，忽的落下，缓缓道：好，好！\n" NOR,
                                       this_object(), ob);
                }

                return;
        }

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("xiaowuxiang", 1) < 130 &&
            (int)ob->query_skill("beiming-shengong", 1) < 130)
        {
                command("say 我逍遥派的本门内功的你都没有学利索，还谈什么？");
                return;
        }

        if ((int)ob->query_skill("force", 1) < 130)
        {
                command("say 我逍遥派的的武功基础就是内功，你先把内功基础打好。");
                return;
        }

        if ((int)ob->query_skill("dodge", 1) < 130)
        {
                command("say 逍遥逍遥，你轻功基础这么差，何谈逍遥？");
                return;
        }

        if (ob->query_int() < 40)
        {
                command("say 我逍遥讲究的就是悟，但是" + RANK_D->query_respect(ob) +
                        "的悟性似乎还有待提高啊。");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("say 你的经验也忒低了点，好好锻炼锻炼再说吧。");
                return;
        }

        command("haha");
        command("say 想不到在这世上竟然还有人可以继承我逍遥派的衣钵！");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/liu", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "你连流月剑舞都未曾学过，何来绝招？";

        if( query("family/gongji", me)<400 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 180)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyue-jian", 1) < 120)
                return "你的流月剑舞火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "点了点头，从怀中轻轻取出了一本"
                       "剑谱，指着其中的一段对\n$N" HIY "不厌其烦的"
                       "细说良久，$N" HIY "一边听一边点头。\n" NOR,
                       me, this_object());

        command("nod");
        command("say 这招的变化看似很烦琐，其实不难，多练习便成。");
        tell_object(me, HIC "你学会了「流月剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/liu", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyue-jian/sheng", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("liuyue-jian", 1) < 1)
                return "你连流月剑舞都未曾学过，何来绝招？";

        if( query("family/gongji", me)<500 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyue-jian", 1) < 140)
                return "你的流月剑舞火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "笑了笑，当即从$N" HIY "手中接过"
                       "长剑，慢慢的演示剑招，$N" HIY "见招\n式优美华"
                       "丽，轻盈灵动，实乃前所谓闻，顿时大有所悟。\n"
                       NOR, me, this_object());

        command("say 这招的关键在于灵动二字，你下去练吧。");
        tell_object(me, HIC "你学会了「天升剑诀」。\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("liuyue-jian"))
                me->improve_skill("liuyue-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyue-jian/sheng", 1, me);
        addn("family/gongji", -500, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/lingbo-weibu/ling", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("lingbo-weibu", 1) < 1)
                return "你连凌波微步都未曾练过，何来洛神凌波？";

        if( query("family/gongji", me)<600 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 180)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("lingbo-weibu", 1) < 120)
                return "你的凌波微步火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "对$N" HIY "微笑道：“想不到"
                       "今日你的轻功能有如此造诣，我便传\n你此招"
                       "，看好了！”说完只见$n" HIY "提起真气，依"
                       "照先天伏羲六十\n四卦将凌波微步由头到尾迅"
                       "速无比的走了一次。但见$n" HIY "意态飘\n逸"
                       "，影子乱飞，真个将逍遥二字发挥得淋漓尽至"
                       "。\n" NOR, me, this_object());

        command("haha");
        command("say 你看懂了多少？");
        tell_object(me, HIC "你学会了「洛神凌波」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("lingbo-weibu"))
                me->improve_skill("lingbo-weibu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingbo-weibu/ling", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/zhong", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你连天山六阳掌都未曾学过，何来绝招？";

        if( query("family/gongji", me)<600 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyang-zhang", 1) < 150)
                return "你的天山六阳掌火候未到，尚且学不了这一招。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑，随即"
                       "便点了点头，将$N" HIY "招至身边，在\n耳旁低声"
                       "细说良久，$N" HIY "听后会心的一笑，看来大有所"
                       "悟。\n" NOR, me, this_object());

        command("haha");
        command("say 对付那些不肯降服之人，用这招最合适不过。");
        tell_object(me, HIC "你学会了「生死符」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/zhong", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/liuyang-zhang/huan", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("liuyang-zhang", 1) < 1)
                return "你连天山六阳掌都未曾学过，何来绝招？";

        if( query("family/gongji", me)<900 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("liuyang-zhang", 1) < 130)
                return "你的天山六阳掌火候未到，尚且学不了这一招。";

        message_vision(HIY "$n" HIY "微微一笑，慢悠悠伸出一掌，正搭"
                       "在$N" HIY "的左肩之上，$N" HIY "稍作\n诧异，"
                       "霎时只觉$n" HIY "内力源源不绝的汹涌而入，异"
                       "种真气注满体\n内，全身竟似快要炸裂开来，不禁"
                       "大惊失色。\n" NOR, me, this_object());

        command("say 你懂了吗？");
        tell_object(me, HIC "你学会了「寰阳式」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("liuyang-zhang"))
                me->improve_skill("liuyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuyang-zhang/huan", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/zhe", me) )
                return "这招我不是已经教会你了吗？";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你连逍遥折梅手都未曾学过，何来绝招？";

        if( query("family/gongji", me)<400 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 120)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("zhemei-shou", 1) < 80)
                return "你的逍遥折梅手火候未到，尚且学不了这一招。";

        message_vision(HIY "$n" HIY "看了看$N" HIY "，微微一笑。当下"
                       "一声清啸，合逍遥折梅手诸多变\n化为一式，随手"
                       "轻轻挥出，招数虚虚实实，煞是精妙。直看得$N"
                       HIY "眼\n花缭乱，目瞪口呆。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 招式便是如此，剩下的就靠你自己了。");
        tell_object(me, HIC "你学会了「折梅式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/zhe", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hai", me) )
                return "这招我不是已经教会你了吗？";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你连逍遥折梅手都未曾学过，何来绝招？";

        if( query("family/gongji", me)<900 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("zhemei-shou", 1) < 130)
                return "你的逍遥折梅手火候未到，尚且学不了这一招。";

        message_vision(HIY "$n" HIY "对$N" HIY "点了点头，当下也不答"
                       "话，单手轻轻一挥而出，手出如\n风，单掌顿时变"
                       "化出漫天掌影，虚虚实实，重重叠叠，霎那间已罩"
                       "\n住$N" HIY "周身穴道，$n" HIY "那掌影却只是"
                       "一沾而过，未伤$N" HIY "半毫。招数\n之巧妙，当"
                       "真只能用“无可比拟”四字形容。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 此招便如海之浩瀚，渊之深绝，可要勤加练习。");
        tell_object(me, HIC "你学会了「海渊式」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hai", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/zhemei-shou/hua", me) )
                return "你自己下去练习吧。";

/*
        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";
*/

        if (me->query_skill("zhemei-shou", 1) < 1)
                return "你连逍遥折梅手都未曾学过，何来绝招？";

        if( query("family/gongji", me)<2500 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if ((int)me->query_skill("beiming-shengong", 1) < 220)
                return "你的北冥神功火候不足，学不成这招。";

        if (me->query_skill("zhemei-shou", 1) < 220)
                return "你的逍遥折梅手火候未到，尚且学不了这一招。";

        if( query("max_neili", me)<3500 )
                return "你的内力修为不够，强运这招会扰乱自身的真元。";

        message_vision(HIY "$n" HIY "对$N" HIY "微微一笑，模样颇为赞"
                       "许，说道：“我在这里给你演示\n一遍，能否领悟"
                       "就全靠你的悟性了。”话音刚落，只见$n" HIY "起"
                       "身\n而立，大袖一挥，掌缘顿时幻起万道霞光，$n"
                       HIY "翻过掌心，掌中\n霞光也随之荡漾。$n" HIY
                       "接着催动内力，霎那间，掌中霞光竟由紫\n变红，"
                       "由红转白……竟接连幻出七种颜色，便宛如一道彩"
                       "虹横架于\n掌心之上。此时，$n" HIY "一声断喝，"
                       "七色掌劲相继迸出掌心。只听\n得“哧哧哧哧哧哧"
                       "哧”七声连响，$N" HIY "对面的石壁竟被$n" HIY
                       "的七色\n掌劲贯穿出七个碗口粗的深穴。\n" NOR,
                       me, this_object());

        command("haha");
        command("say 这招乃是我毕生精力所创，刚才不过是一成的威力罢了。");
        command("say 非到性命不保，绝不可轻易施展此招。");
        tell_object(me, HIC "你学会了「化妖功」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("zhemei-shou"))
                me->improve_skill("zhemei-shou", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        if (me->can_improve_skill("beiming-shengong"))
                me->improve_skill("beiming-shengong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/zhemei-shou/hua", 1, me);
        addn("family/gongji", -2500, me);
        return 1;

}

mixed ask_zhihuan()
{
        int cost;
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "逍遥派" )
                return "给我滚开！";

        if( query("family/master_id", me) != query("id") )
                return "你还不配！";

        if (me->query_skill("zhemei-shou", 1) < 200 &&
           me->query_skill("liuyang-zhang", 1) < 200)
                return "你拿去也没用。";

        if( query("family/first", me) ) cost = 250;
        else cost = 500;

        if( query("family/gongji", me) < cost )
                return "你为逍遥派所做的贡献不够，逍遥神仙环我不能给你。\n";

        ob = find_object(ZHIHUAN);
        if (! ob) ob = load_object(ZHIHUAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "本门的信物不就在你手中吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了，逍遥神仙环现在不在我手中。";

                if( query("family/family_name", owner) == "逍遥派" )
                        return "逍遥神仙环现在落在本派"+query("name", owner)+
                               "手中，你要用就去找他吧。";
                else
                        return "我正为此事担忧呢，本门信物现在落入了"+query("name", owner)+
                               "之手，你赶快去把他杀了，把指环取回来！";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "微微一笑，道：“这逍遥神仙环你便拿去，希"
                       "望日后你能继承我的衣钵。”\n" NOR, this_object(), me);
        command("give shenxian huan to "+query("id", me));
        addn("family/gongji", -cost, me);

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "灰飞烟灭" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/hui",
                           "name"    : "灰飞烟灭",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 150,
                           "sk2"     : "liuyang-zhang",
                           "lv2"     : 150,
                           "neili"   : 2000,
                           "gongxian": 1000, ]));
                break;

        case "九部式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/jiubu",
                           "name"    : "九部式",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "free"    : 1,
                           "gongxian": 1000, ]));
                break;

        case "空手入白刃" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zhemei-shou/duo",
                           "name"    : "空手入白刃",
                           "sk1"     : "zhemei-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "free"    : 1,
                           "neili"   : 1400, ]));
                break;

        case "白虹掌力" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/baihong",
                           "name"    : "白虹掌力",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 100,
                           "free"    : 1,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000, ]));
                break;

        case "九天式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/jiutian",
                           "name"    : "九天式",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "free"    : 1,
                           "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        case "神光离合" :
               return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/lingbo-weibu/shen",
                               "name"    : "神光离合",
                             "sk1"     : "lingbo-weibu",
                               "lv1"     : 220,
                             "sk2"     : "dodge",
                            "free"    : 1,
                             "lv2"     : 320,
                             "gongxian": 1600,
                             "neili"   : 1400, ]));
                  break;
        case "破神诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuyang-zhang/po",
                           "name"    : "破神诀",
                           "sk1"     : "liuyang-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "free"    : 1,
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        default:
                return 0;
        }
}
