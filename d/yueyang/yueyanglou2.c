// Room: /d/yueyang/yueyanglou2.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳阳楼二楼");
        set("long", @LONG
岳阳楼二楼内嵌有一幅《岳阳楼记》(ji)雕屏，此雕屏为清代大书
法家张照所写，字形方正，笔力雄浑技术法多变，狮人匠心、为传世极
品。
    岳阳地方山重水阔，文渊灵毓，竟成了贬官们的钟爱之地。上自屈
原，涉足岳阳的各朝名家大都仕途坎坷，累有贬迹。无论去国怀乡，忧
馋畏讥也好；心旷神怡，宠辱皆忘也好，只要贬官们踏上岳阳这块土地，
总是文思泉涌，佳作迭出。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "up"   : __DIR__"yueyanglou3",
                "down" : __DIR__"yueyanglou1",
        ]));
        set("item_desc", ([
                "ji" : "
                    岳阳楼记
                    　　　　　　　　　范仲淹
　
　　庆历四年春，滕子京谪守巴陵郡。越明年，政通人和，百废俱兴，
乃重修岳阳楼，增其旧制，刻唐贤今人之诗赋于其上，属予作文以记之。

　　予观夫巴陵胜状，在洞庭一湖。衔远山，吞长江，浩浩荡荡，横无
际涯，朝晖夕阴，气象万千。此则岳阳楼之大观也，前人之述备矣。然
则北通巫峡，南极潇湘，迁客骚人，多会于此。览物之情，得无异乎？

　　若夫霪雨霏霏，连月不开；阴风怒号，浊浪排空；日星隐曜，山岳
潜形；商旅不行，樯倾楫摧；薄暮冥冥，虎啸猿啼；登斯楼也，则有去
国怀乡，忧谗畏讥，满目萧然，感极而悲者矣。

　　至若春和景明，波澜不惊；上下天光，一碧万顷；沙鸥翔集，锦麟
游泳；岸芷汀兰，郁郁青青。而或长烟一空，皓月千里；浮光耀金，静
影沉璧；渔歌互答，此乐何极。登斯楼也，则有心旷神怡，宠辱皆忘，
把酒临风，其喜洋洋者矣。

　　嗟夫！予尝求古仁人之心，或异二者之为何哉？不以物喜，不以己
悲。居庙堂之高，则忧其民；处江湖之远，则忧其君。是进亦忧，退亦
忧，然则何时而乐耶？其必曰：先天下之忧而忧，天下之乐而乐欤。噫，
微斯人，吾谁与归。\n"
        ]));
	set("coor/x", -6240);
	set("coor/y", -3000);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}