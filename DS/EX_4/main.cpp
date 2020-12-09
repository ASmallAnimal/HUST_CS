#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "def.h"
#include "stu.h"

int main() {
    /*变量定义*/
    Graphs ghs;  //多图结构体的声明
    ALGraph G;   //单个图的声明
    int op = 1;  //功能选择的声明
    int i, j, k;  //循环变量
    int n;  //图的个数
    int ukey, vkey, wkey; //要进行查找的关键字
    int s; //函数返回状态值
    char name[30];  //图的名字
    char FileName[100]; //文件保存地址
    VertexType value; //新的赋值顶点
    //多图的初始化
    for (i = 0; i <= 20; i++) {
        ghs.elem[i].graph.kind = UDG;
    }//全都定义为无向图
    ghs.length = 0;
    while (op) {
        system("cls");    //用于清屏
        printf("\n\n");
        printf("\t\t      Menu for Undirected Graph On Chain Structure \n");
        printf("\t******************************************************************************\n");
        printf("\t\t\t1.  创建图 \t\t\t2.  销毁图\n");
        printf("\t\t\t3.  查找顶点 \t\t\t4. 顶点赋值\n");
        printf("\t\t\t5.  获得第一邻接点\t\t 6.  获得下一邻接点\n");
        printf("\t\t\t7.  插入顶点 \t\t\t8.  删除顶点\n");
        printf("\t\t\t9.  插入弧  \t\t       10. 删除弧\n");
        printf("\t\t\t11. 深度优先搜索遍历\t\t 12. 广度优先搜索遍历\n");
        printf("\t\t\t13. 保存图 \t\t       14. 加载图\n");
        printf("\t\t\t15. 遍历图\t\t       16.  遍历多图\n");
        printf("\t\t\t\t\t**0. 退出**\n");
        printf("\t******************************************************************************\n");
        printf("\t\t\t请选择你的操作[0-16]: ");
        scanf("%d", &op);
        switch (op) {
            case 1:  //添加图
                printf("当前操作：添加图\n");
                printf("请输入要添加的图的个数");
                scanf("%d", &n);
                while (n--) {
                    printf("请输入要添加的图的名称\n");
                    scanf("%s", name);
                    AddGraphs(ghs, name);  //增加图
                    printf("请输入图的顶点和弧的相关信息：\n");
                    VertexType V[30];  //顶点的信息
                    KeyType VR[100][2]; //弧的信息
                    i = 0;
                    do {
                        scanf("%d%s", &V[i].key, V[i].others);
                    } while (V[i++].key != -1);
                    i = 0;
                    do {
                        scanf("%d%d", &VR[i][0], &VR[i][1]);
                    } while (VR[i++][0] != -1);
                    if (CreateGraph(ghs.elem[ghs.length - 1].graph, V, VR) == ERROR){
                        free(ghs.elem[ghs.length-1].name);
                        ghs.length--;
                        printf("输入数据错，无法创建\n");
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                //遍历多线性表
                GraphsTraverse(ghs);
                printf("\n");
                getchar();
                getchar();
                break;
            case 2:  //销毁图
                printf("当前操作：销毁图\n");
                printf("请输入要销毁的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        DestroyGraph(ghs.elem[i].graph);
                        free(ghs.elem[i].name);
                        ghs.length--;
                        while (i < ghs.length) {
                            ghs.elem[i] = ghs.elem[i + 1];
                            i++;
                        }
                        printf("销毁成功，可以遍历多图查看销毁结果\n");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 3: //查找顶点
                printf("当前操作：查找顶点\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入要查找的关键字：");
                        scanf("%d", &ukey);
                        s = LocateVex(ghs.elem[i].graph, ukey);
                        if (s != -1)
                            printf("查找成功：%d %s", s, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("查找失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 4:
                printf("当前操作：顶点赋值\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入重新赋值的顶点的关键字和赋值后的信息：");
                        scanf("%d%d%s", &ukey, &value.key, value.others);
                        s = PutVex(ghs.elem[i].graph, ukey, value);
                        if (s == OK){
                            printf("修改成功！\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("赋值操作失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 5:
                printf("当前操作：获得第一邻接点\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行操作的顶点的关键字：");
                        scanf("%d", &ukey);
                        s = FirstAdjVex(ghs.elem[i].graph, ukey);
                        if (s != -1)
                            printf("查找成功：%d %s", ghs.elem[i].graph.vertices[s].data.key, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("查找失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 6:
                printf("当前操作：获得下一邻接点\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行操作的顶点的关键字：");
                        scanf("%d%d", &vkey, &wkey);
                        s = NextAdjVex(ghs.elem[i].graph, vkey, wkey);
                        if (s != -1)
                            printf("查找成功：%d %s", ghs.elem[i].graph.vertices[s].data.key, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("无下一邻接顶点");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 7:
                printf("当前操作：插入顶点\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行操作的顶点的信息：");
                        scanf("%d%s", &value.key, value.others);
                        s = InsertVex(ghs.elem[i].graph, value);
                        if (s != -1)
                        {
                            printf("插入顶点成功\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("插入操作失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 8:
                printf("当前操作：删除顶点\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行删除操作的顶点的关键字：");
                        scanf("%d", &vkey);
                        s = DeleteVex(ghs.elem[i].graph, vkey);
                        if (s == OK){
                            printf("删除顶点成功\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("删除操作失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 9:
                printf("当前操作：插入弧\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行操作的顶点的信息：");
                        scanf("%d%d", &vkey, &wkey);
                        s = InsertArc(ghs.elem[i].graph, vkey,wkey);
                        if (s == OK)
                        {
                            printf("插入弧成功\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("插入弧操作失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 10:
                printf("当前操作：删除弧\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入进行删除操作的顶点的关键字：");
                        scanf("%d%d", &vkey,&wkey);
                        s = DeleteArc(ghs.elem[i].graph, vkey,wkey);
                        if (s == OK){
                            printf("删除弧成功\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("删除操作失败");
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 11:
                printf("当前操作：深度优先遍历\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        DFSTraverse(ghs.elem[i].graph,visit);
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 12:
                printf("当前操作：广度优先遍历\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        BFSTraverse(ghs.elem[i].graph,visit);
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 13:
                printf("当前操作：保存图\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入文件保存的地址\n");
                        scanf("%s",FileName);
                        s=SaveGraph(ghs.elem[i].graph,FileName);
                        if(s==OK){
                            printf("保存成功");
                            DestroyGraph(ghs.elem[i].graph);
                        }
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 14:
                printf("当前操作：加载图\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("请输入文件读取的地址\n");
                        scanf("%s",FileName);
                        LoadGraph(ghs.elem[i].graph,FileName);
                        Traverse(ghs.elem[i].graph);
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 15:
                printf("当前操作：遍历图\n");
                printf("请输入要进行操作的图的名字:");
                scanf("%s", name);
                //匹配名字
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        Traverse(ghs.elem[i].graph);
                        break;
                    }
                }
                if (i==ghs.length) printf("未匹配到相应名字的图");
                getchar();
                getchar();
                break;
            case 16:
                printf("当前操作：遍历多图\n");
                GraphsTraverse(ghs);
                getchar();
                getchar();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    printf("欢迎下次在使用本系统！\n");
    return 1;
}