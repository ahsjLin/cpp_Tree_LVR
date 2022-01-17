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
int n_node_now=0;

struct BSTNode * newBSTNode(int newNode){
	struct BSTNode * rootNode = new struct BSTNode;
	if(Form1->CheckBox1->Checked){
		String str = "Create new node and place (" + IntToStr(newNode) +")";
		Form1->Memo2->Lines->Add(str);
		Form1->Memo2->Lines->Add("");
	}
	if(StrToInt(Form1->Edit1->Text)==++n_node_now) {
		insert_order += IntToStr(newNode);
		n_node_now=0;
	}
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
		if(Form1->CheckBox1->Checked){
			String str = "Finding leaf (" + IntToStr(newNode) + ") -> go left";
			Form1->Memo2->Lines->Add(str);
		}
		node->leftchild = insertBST(node->leftchild, newNode);
	}
	else{
		if(Form1->CheckBox1->Checked){
			String str = "Finding leaf (" + IntToStr(newNode) + ") -> go right";
			Form1->Memo2->Lines->Add(str);
		}
		node->rightchild = insertBST(node->rightchild, newNode);
	}
	return node;
}
void deleteBST(struct BSTNode* root){
	if(root!=NULL){
		deleteBST(root->leftchild);
		deleteBST(root->rightchild);
		if(Form1->CheckBox1->Checked){
			String str = "Delete node(" + IntToStr(root->data)+")";
			Form1->Memo3->Lines->Add(str);
		}
		delete root;
		//Form1->Memo3->Lines->Add("");
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
	if(n_node>1000 && CheckBox1->Checked)
	{
		ShowMessage("Less than 1000. Closed show processing");
		CheckBox1->Checked = false;
	}
	else if(n_node>1000000)  {
		ShowMessage("No. No. Don't do that.");
		CheckBox1->Checked = false;
        return;
    }
	// spanning tree time
	clock_t t1 = clock();
	srand(time(NULL));
	for(int i=0; i<n_node; i++){
		newNode = rand()%10000;
		root = insertBST(root, newNode);
	}
	clock_t t2 = clock();
	double d = ((double)(t2-t1))/CLOCKS_PER_SEC;

	tree = "";

	printBST(root);

	String str = "Spanning time: " + FloatToStr(d) +"s";

	Memo1->Lines->Add("The order of inserted value:");
	Memo1->Lines->Add(insert_order);
    insert_order = "";
	Memo1->Lines->Add("");
	Memo1->Lines->Add("The LVR way to show data of nodes in tree:");
	Memo1->Lines->Add(tree);

	Memo2->Lines->Add("");
	Memo2->Lines->Add(str);


	Memo3->Lines->Add("The LRV way to Delete nodes.");
	clock_t t3 = clock();
	deleteBST(root);
	clock_t t4 = clock();
	d = ((double)(t4-t3))/CLOCKS_PER_SEC;
	str = "Detele time: " + FloatToStr(d) +"s";
	Memo3->Lines->Add("");
	Memo3->Lines->Add(str);
	root = NULL;
	//ShowMessage("t1" + FloatToStr(t1)+"\nt1" + FloatToStr(t2)+"\nd:" + FloatToStr(d));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Edit1->Text = TrackBar1->Position;
}
//---------------------------------------------------------------------------

