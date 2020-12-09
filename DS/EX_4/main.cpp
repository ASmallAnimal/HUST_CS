#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "def.h"
#include "stu.h"

int main() {
    /*��������*/
    Graphs ghs;  //��ͼ�ṹ�������
    ALGraph G;   //����ͼ������
    int op = 1;  //����ѡ�������
    int i, j, k;  //ѭ������
    int n;  //ͼ�ĸ���
    int ukey, vkey, wkey; //Ҫ���в��ҵĹؼ���
    int s; //��������״ֵ̬
    char name[30];  //ͼ������
    char FileName[100]; //�ļ������ַ
    VertexType value; //�µĸ�ֵ����
    //��ͼ�ĳ�ʼ��
    for (i = 0; i <= 20; i++) {
        ghs.elem[i].graph.kind = UDG;
    }//ȫ������Ϊ����ͼ
    ghs.length = 0;
    while (op) {
        system("cls");    //��������
        printf("\n\n");
        printf("\t\t      Menu for Undirected Graph On Chain Structure \n");
        printf("\t******************************************************************************\n");
        printf("\t\t\t1.  ����ͼ \t\t\t2.  ����ͼ\n");
        printf("\t\t\t3.  ���Ҷ��� \t\t\t4. ���㸳ֵ\n");
        printf("\t\t\t5.  ��õ�һ�ڽӵ�\t\t 6.  �����һ�ڽӵ�\n");
        printf("\t\t\t7.  ���붥�� \t\t\t8.  ɾ������\n");
        printf("\t\t\t9.  ���뻡  \t\t       10. ɾ����\n");
        printf("\t\t\t11. ���������������\t\t 12. ���������������\n");
        printf("\t\t\t13. ����ͼ \t\t       14. ����ͼ\n");
        printf("\t\t\t15. ����ͼ\t\t       16.  ������ͼ\n");
        printf("\t\t\t\t\t**0. �˳�**\n");
        printf("\t******************************************************************************\n");
        printf("\t\t\t��ѡ����Ĳ���[0-16]: ");
        scanf("%d", &op);
        switch (op) {
            case 1:  //���ͼ
                printf("��ǰ���������ͼ\n");
                printf("������Ҫ��ӵ�ͼ�ĸ���");
                scanf("%d", &n);
                while (n--) {
                    printf("������Ҫ��ӵ�ͼ������\n");
                    scanf("%s", name);
                    AddGraphs(ghs, name);  //����ͼ
                    printf("������ͼ�Ķ���ͻ��������Ϣ��\n");
                    VertexType V[30];  //�������Ϣ
                    KeyType VR[100][2]; //������Ϣ
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
                        printf("�������ݴ��޷�����\n");
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                //���������Ա�
                GraphsTraverse(ghs);
                printf("\n");
                getchar();
                getchar();
                break;
            case 2:  //����ͼ
                printf("��ǰ����������ͼ\n");
                printf("������Ҫ���ٵ�ͼ������:");
                scanf("%s", name);
                //ƥ������
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
                        printf("���ٳɹ������Ա�����ͼ�鿴���ٽ��\n");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 3: //���Ҷ���
                printf("��ǰ���������Ҷ���\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("������Ҫ���ҵĹؼ��֣�");
                        scanf("%d", &ukey);
                        s = LocateVex(ghs.elem[i].graph, ukey);
                        if (s != -1)
                            printf("���ҳɹ���%d %s", s, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("����ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 4:
                printf("��ǰ���������㸳ֵ\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("���������¸�ֵ�Ķ���Ĺؼ��ֺ͸�ֵ�����Ϣ��");
                        scanf("%d%d%s", &ukey, &value.key, value.others);
                        s = PutVex(ghs.elem[i].graph, ukey, value);
                        if (s == OK){
                            printf("�޸ĳɹ���\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("��ֵ����ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 5:
                printf("��ǰ��������õ�һ�ڽӵ�\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("��������в����Ķ���Ĺؼ��֣�");
                        scanf("%d", &ukey);
                        s = FirstAdjVex(ghs.elem[i].graph, ukey);
                        if (s != -1)
                            printf("���ҳɹ���%d %s", ghs.elem[i].graph.vertices[s].data.key, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("����ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 6:
                printf("��ǰ�����������һ�ڽӵ�\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("��������в����Ķ���Ĺؼ��֣�");
                        scanf("%d%d", &vkey, &wkey);
                        s = NextAdjVex(ghs.elem[i].graph, vkey, wkey);
                        if (s != -1)
                            printf("���ҳɹ���%d %s", ghs.elem[i].graph.vertices[s].data.key, ghs.elem[i].graph.vertices[s].data.others);
                        else
                            printf("����һ�ڽӶ���");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 7:
                printf("��ǰ���������붥��\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("��������в����Ķ������Ϣ��");
                        scanf("%d%s", &value.key, value.others);
                        s = InsertVex(ghs.elem[i].graph, value);
                        if (s != -1)
                        {
                            printf("���붥��ɹ�\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("�������ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 8:
                printf("��ǰ������ɾ������\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("���������ɾ�������Ķ���Ĺؼ��֣�");
                        scanf("%d", &vkey);
                        s = DeleteVex(ghs.elem[i].graph, vkey);
                        if (s == OK){
                            printf("ɾ������ɹ�\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("ɾ������ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 9:
                printf("��ǰ���������뻡\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("��������в����Ķ������Ϣ��");
                        scanf("%d%d", &vkey, &wkey);
                        s = InsertArc(ghs.elem[i].graph, vkey,wkey);
                        if (s == OK)
                        {
                            printf("���뻡�ɹ�\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("���뻡����ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 10:
                printf("��ǰ������ɾ����\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("���������ɾ�������Ķ���Ĺؼ��֣�");
                        scanf("%d%d", &vkey,&wkey);
                        s = DeleteArc(ghs.elem[i].graph, vkey,wkey);
                        if (s == OK){
                            printf("ɾ�����ɹ�\n");
                            Traverse(ghs.elem[i].graph);
                        }
                        else
                            printf("ɾ������ʧ��");
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 11:
                printf("��ǰ������������ȱ���\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        DFSTraverse(ghs.elem[i].graph,visit);
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 12:
                printf("��ǰ������������ȱ���\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        BFSTraverse(ghs.elem[i].graph,visit);
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 13:
                printf("��ǰ����������ͼ\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("�������ļ�����ĵ�ַ\n");
                        scanf("%s",FileName);
                        s=SaveGraph(ghs.elem[i].graph,FileName);
                        if(s==OK){
                            printf("����ɹ�");
                            DestroyGraph(ghs.elem[i].graph);
                        }
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 14:
                printf("��ǰ����������ͼ\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        printf("�������ļ���ȡ�ĵ�ַ\n");
                        scanf("%s",FileName);
                        LoadGraph(ghs.elem[i].graph,FileName);
                        Traverse(ghs.elem[i].graph);
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 15:
                printf("��ǰ����������ͼ\n");
                printf("������Ҫ���в�����ͼ������:");
                scanf("%s", name);
                //ƥ������
                for (i = 0; i < ghs.length; i++) {
                    j = strcmp(ghs.elem[i].name, name);
                    if (j == 0) {
                        Traverse(ghs.elem[i].graph);
                        break;
                    }
                }
                if (i==ghs.length) printf("δƥ�䵽��Ӧ���ֵ�ͼ");
                getchar();
                getchar();
                break;
            case 16:
                printf("��ǰ������������ͼ\n");
                GraphsTraverse(ghs);
                getchar();
                getchar();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 1;
}