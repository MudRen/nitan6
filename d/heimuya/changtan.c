// Room: /d/heimuya/changtan.c

inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_yell(string arg);
void reset();

void create()
{
    set("short", "长滩");
        set("long", @LONG
这片长滩不时有日月教教众乘船(boat)往来，滩头插着一面日月
教的旗帜，表明这里是日月教的所控制的，所以尽管江面上往来的船
只很多，但是并没有船敢在这里停留，要过对岸只有靠日月教自己的
船只了。
LONG );
    set("item_desc", ([
        "he" : "一叶小舟静森森地靠在芦苇畔，喊(yell)一声试看。\n",
    ]));
  set("exits",([
      "westup" : __DIR__"shandao1",
  ]));

    set("objects", ([
        CLASS_D("riyue") + "/huangboliu": 1,
        __DIR__"npc/heiyiren" : 2,
    ]));
    set("no_clean_up", 0);
    set("outdoors", "heimuya");
        set("boat",1);
        set("opposite", __DIR__"xingxingtan");
    setup();
}

void init()
{
    add_action("do_yell", "yell");
    add_action("do_cross", "cross");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"duchuan1")) )
            room = load_object(__DIR__"duchuan1");
        if( room = find_object(__DIR__"duchuan1") ) {
            if( query("yell_trigger", room) == 0){
                set("yell_trigger", 1, room);
                set("exits/enter", __DIR__"duchuan1");
                set("exits/out", __FILE__, room);
                message("vision", "一叶扁舟缓缓地驶了过来，艄公将一块踏脚"
                    "板搭上堤岸，以便乘客\n上下。\n", this_object() );
                message("vision", "艄公将一块踏脚板搭上堤岸，形成一个向上"
                    "的阶梯。\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "只听得风浪中隐隐传来：“别急嘛，"
                    "这儿正忙着呐……”\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
        message("vision", "岸边一只渡船上的老艄公说道：正等着你呢，上来吧。\n",
            this_object() );
}


void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "艄公把踏脚板收了起来，竹篙一点，扁舟向河中撑去。\n",
        this_object() );

    if( room = find_object(__DIR__"duchuan1") )
    {
        delete("exits/out", room);
        message("vision", "艄公把踏脚板收起来，说了一声“坐稳喽”，"
            "竹篙一点，扁舟向\n河中撑去。\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") )
    {
        set("exits/out", __DIR__"xingxingtan", room);
        message("vision", "艄公说“到啦，上岸吧”，随即把一块踏脚板"
            "搭上堤岸。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan1") ) {
        delete("exits/out", room);
        message("vision","艄公把踏脚板收起来，把扁舟撑向河近岸。\n", room);
        delete("yell_trigger", room);
    }
}

int do_yell(string arg)
{
    string dir;

    if( !arg || arg=="" ) return 0;

    if( arg=="boat" ) arg = "船家";
    if( query("age", this_player())<16 )
        message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n",
            this_player());
    else if( query("neili", this_player())>500 )
        message_vision("$N吸了口气，一声“" + arg + "”，声音中正平和地远远传"
            "了出去。\n", this_player());
    else
        message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n",
            this_player());
    if( arg=="船家")
    {
        check_trigger();
        return 1;
    }
    else
        message_vision("风浪中远远传来一阵回声：“" + arg +
            "～～～”\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan1") )
        delete("yell_trigger", room);
}

int do_cross()
{
    object me = this_player();

    if( query("family/family_name", me) != "日月神教" )
         return notify_fail("什么？\n");

    if (me->query_skill("piaomiao-shenfa",1) < 100) 
    {
         tell_object(me, random(2) ? "你觉得江面太宽，没有十足的把握跃过去。\n"
                     : "你看着波涛汹涌的江面，心里不禁打了个突，没敢乱来。\n");
         return 1;
    }

    if( query("neili", me)<100 )
    {
         tell_object(me, "你的内力不够，还是休息一下再说吧。\n");
         return 1;
    }

    addn("neili", -50, me);
    message_vision("$N身形一晃，施展出飘渺身法，只见$P足尖点水，渐渐远去。\n", me);
    tell_object(me, "你顺利的到达了彼岸！\n");
    me->move(__DIR__"xingxingtan");
    return 1;
}

int valid_leave(object me, string dir)
{
    object guarder;

    if (! objectp(guarder = present("huang boliu", this_object())))
          return 1;

    if (dir == "westup")
          return guarder->permit_pass(me, dir);

    return 1;
}

