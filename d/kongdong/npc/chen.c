inherit NPC;


void create()
{
    set_name("陈汉京", ({ "chen hanjing","chen","jing" }) );
    set("title","崆峒派大师兄");
    set("gender", "男性" );
    set("class","taoist");
    set("positive_score",8000);
    set("age",25);
	set_hp("sen", 600 );
	set_hp("kee", 600 );
	create_family("崆峒派", 2, "弟子");
    set_wugong("jiben-qinggong",100,100);
    set_wugong("nieyun-bufa",60,65,1);
    set_wugong("luofeng",50,50,1);
	set_xiuwei_by_type("dodge",500);
    set_wugong("unarmed",100,100);
    set_wugong("dahong-quan",100,100);
    set_wugong("shizi-zhan",90,86,1);
    set_wugong("wulong-quan",60,60,1);
	set_xiuwei("unarmed",800);
    set("social_exp",2000);
    set("combat_exp",10000);
    set("force",200);
    set("max_force",200);
    set("force_factor",10);
    setup();
    carry_object(__DIR__"obj/cloth2")->wear();
}

void init()
{
        object ob;
        ob = this_player();
       ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("say_hi");
            call_out("say_hi",1,ob);
            }
}

void say_hi(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        if(ob->query("family/family_name")!="崆峒派")
        {
                message_vision("陈汉京向$N一拱手：这位"+RANK_D->query_respect(ob)+"，"
                "家师就在里面，快请进吧。\n",ob);
			return;
        }
        message_vision("陈汉京笑着拍拍$N的肩膀：怎么样，功夫有长进吗？好好练吧。\n",ob);
		return;
}

                
int accept_object( object ppl, object obj )
{
    object gold;

    if ( obj->query( "id" ) != "teng xia" ) 
        return 0;
    if ( query( "box" ) )               
    {
        message_vision( "陈汉京冲着$N大喝道：“周老太爷怎么会让你送两个礼盒？！"
            + RANK_D->query_rude( ppl ) + "竟敢欺骗老夫！”\n", ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }

    if ( ppl->query( "mud_age" ) < 3600 * 24 * 2        //如果玩家年龄在十六以下
        && ppl->query( "combat_exp" ) < 50000           //或经验不足一万，
        && ppl->query( "max_force" ) < 1000 )            //或内力不足三百，则否认
    {
        message_vision ( "陈汉京上下打量了$N许久，突然嘿嘿冷笑道：“哼！就凭你\n"
            + "这么点道行，也能走镖？你是怎么来的，还不老实交代！！”\n",
            ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }
        
    message_vision( "陈汉京拍拍$N肩头，笑了笑道：“很好，不愧是周老太爷的镖师。\n"
        + "这些是你走镖的报酬，拿好哦。”\n", ppl );
    call_out( "Dest", 1, obj );
    set( "box", 1 );                    
    gold = new( MONEY_DIR + "gold" );       
    gold->set_amount( 10 );
    gold->move( ppl );
    command("chat 恭喜，"+ppl->query("name")+"("+ppl->query("id")+")"+"走镖成功，获得十两金子的报酬。");
    return 1;
}

void Dest( object obj )
{
       destruct( obj );
}

