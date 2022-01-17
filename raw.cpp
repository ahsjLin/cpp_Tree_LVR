//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "kruskal_spanning_tree.h"
#include <stdlib.h>
#include <time.h>
struct BSTNode {
	struct BSTNode * leftchild=NULL;
	int data;
	struct BSTNode * rightchild=NULL;
};
struct BSTNode *root;
String tree = "";
String insert_order = "";
int n_node=0;

struct BSTNode * newBSTNode(int newNode){
	struct BSTNode * rootNode = new struct BSTNode;
	String str = "Create new node and place (" + IntToStr(newNode) +")";
	Form1->Memo2->Lines->Add(str);
	Form1->Memo2->Lines->Add("");
	if(StrToInt(Form1->Edit1->Text)==++n_node)
		insert_order += IntToStr(newNode);
	else
		insert_order += IntToStr(newNode) +" -> ";
	rootNode->data = newNode;
	rootNode->leftchild = rootNode->rightchild = NULL;
	return rootNode;
}

void printBST(struct BSTNode *node){
	if(node!=NULL){
		printBST(node->leftchild);
		tree += IntToStr(node->data) + "_";
		printBST(node->rightchild);
	}
}

struct BSTNode * insertBST(struct BSTNode* node, int newNode){
	if(node==NULL) return newBSTNode(newNode);
	if(node->data>=newNode){
		String str = "Finding leaf (" + IntToStr(newNode) + ") -> go left";
		Form1->Memo2->Lines->Add(str);
		node->leftchild = insertBST(node->leftchild, newNode);
	}
	else{
		String str = "Finding leaf (" + IntToStr(newNode) + ") -> go right";
		Form1->Memo2->Lines->Add(str);
		node->rightchild = insertBST(node->rightchild, newNode);
	}
	return node;
}
void deleteBST(struct BSTNode* root){
	if(root!=NULL){
		deleteBST(root->leftchild);
		deleteBST(root->rightchild);
		String str = "Delete node(" + IntToStr(root->data)+")";
		Form1->Memo3->Lines->Add(str);
		delete root;
		Form1->Memo3->Lines->Add("");
	}

}
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	Memo2->Lines->Clear();
	Memo3->Lines->Clear();
	//int newNode = StrToInt(Edit1->Text);
	int newNode, n_node;
	n_node = StrToInt(Edit1->Text);
	if(n_node<=0)
	{ ShowMessage("Please input greater than 0.");
		return;
	}
	if(n_node>1000)
	{
		ShowMessage("Less than 1000.");
		return;
	}
	srand(time(NULL));
	for(int i=0; i<n_node; i++){
		newNode = rand()%10000;
		root = insertBST(root, newNode);
	}
	tree = "";
	printBST(root);
	Memo1->Lines->Add("Order of inserted value:");
	Memo1->Lines->Add(insert_order);
	Memo1->Lines->Add("");
	Memo1->Lines->Add("The LRV way to show value of node in tree:");
	Memo1->Lines->Add(tree);
	deleteBST(root);
	root = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Edit1->Text = TrackBar1->Position;
}
//---------------------------------------------------------------------------
