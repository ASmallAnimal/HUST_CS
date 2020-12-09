//
// Created by spiri on 2020/11/25.
//

#ifndef EX_4_DEF_H
#define EX_4_DEF_H

#endif //EX_4_DEF_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef int Boolean;
typedef enum {UNKOWN,DG,DN,UDG,UDN} GraphKind;
Boolean visited[MAX_VERTEX_NUM];

typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //�������Ͷ���

typedef struct ArcNode {         //�������Ͷ���
    int adjvex;              //����λ�ñ��
    struct ArcNode  *nextarc;       //��һ������ָ��
} ArcNode;

typedef struct VNode{                //ͷ��㼰���������Ͷ���
    VertexType data;           //������Ϣ
    ArcNode *firstarc;           //ָ���һ����
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;          //ͷ�������
    int vexnum,arcnum;         //������������
    GraphKind  kind;        //ͼ������
} ALGraph;

typedef struct {
    struct {
        char name[30];
        ALGraph graph;
    } elem[100];
    int length;
    int listsize;
} Graphs;

typedef struct{
    int data[MAX_VERTEX_NUM];
    int front;
    int rear;
}Queue;