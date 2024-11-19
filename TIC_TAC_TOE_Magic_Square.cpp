#include<iostream>
using namespace std;
#include<vector>
#include<unordered_map>
vector<int>board(9,2);
int turn = 1;
void display() {
  for (int i = 0; i < 9; i++) {
    if (i == 3 || i == 6) {
      cout << endl;
}
  if (board[i] == 3) {
    cout << "X ";
   } 
   else if (board[i] == 5) {
      cout << "O ";
  } 
  else {
     cout << "- ";
}
}
    cout << endl;
}
int make2(vector<int>&board){
    if(board[4] == 2){
      return 4;
 }
else{
for(int i=0;i<9;i++){
if(board[i] == 2){
return i;
}
}
}
return -1;
}
void go(int n){
if(turn%2==0){
board[n] = 5;
}
else{
board[n] = 3;
}
turn = turn + 1;
}
int posswinX(vector<int>&board){
vector<int>pos;
vector<int>magicsquare = {8,3,4,1,5,9,6,7,2};
vector<int>valstore;
for(int i=0;i<9;i++){
if(board[i] == 3){
pos.push_back(i);
}
}
for(int i=0;i<9;i++)
{
for(int j=0;j<pos.size();j++)
{
if(i == pos[j])
{
valstore.push_back(magicsquare[i]);
}
}
}
vector<int>results;
for (int i = 0; i < valstore.size(); i++) {
for (int j = i + 1; j < valstore.size(); j++) {
int pairsum = valstore[i] + valstore[j];
int result = 15 - pairsum;
results.push_back(result);
}
}
vector<int>finalpostions;
for(int i=0;i<9;i++){
for(int j=0;j<results.size();j++){
if(magicsquare[i] == results[j])
{
finalpostions.push_back(i);
}
}
}
for(int j=0;j<finalpostions.size();j++){
if(board[finalpostions[j]]==2){
return finalpostions[j];
}
}
return -1; // if no chance of winning
}
int posswinO(vector<int>&board){
vector<int>pos;
vector<int>magicsquare = {8,3,4,1,5,9,6,7,2};
vector<int>valstore;
for(int i=0;i<9;i++){
if(board[i] == 5){
pos.push_back(i);
}
}
for(int i=0;i<9;i++)
{
for(int j=0;j<pos.size();j++)
{
if(i == pos[j])
{
valstore.push_back(magicsquare[i]);
}
}
}
vector<int>results;
for (int i = 0; i < valstore.size(); i++) {
for (int j = i + 1; j < valstore.size(); j++) {
int pairsum = valstore[i] + valstore[j];
int result = 15 - pairsum;
results.push_back(result);
}
}
vector<int>finalpostions;
for(int i=0;i<9;i++){
for(int j=0;j<results.size();j++){
if(magicsquare[i] == results[j])
{
finalpostions.push_back(i);
}
}
}
for(int j=0;j<finalpostions.size();j++){
if(board[finalpostions[j]]==2){
return finalpostions[j];
}
}
return -1; // if no chance of winning
}
void checkwinX(vector<int>&board){
vector<int>pos;
vector<int>magicsquare = {8,3,4,1,5,9,6,7,2};
vector<int>valstore;
for(int i=0;i<9;i++){
if(board[i] == 3){
pos.push_back(i);
}
}
for(int i=0;i<9;i++)
{
for(int j=0;j<pos.size();j++)
{
if(i == pos[j])
{
valstore.push_back(magicsquare[i]);
}
}
}
vector<int>results;
for (int i = 0; i < valstore.size(); i++) {
for (int j = i + 1; j < valstore.size(); j++) {
for (int k = i + 2; k < valstore.size(); k++) {
if((valstore[i] + valstore[j] + valstore[k]) == 15){
cout << endl;
cout << "player 1 wins " << endl;
exit(1);
}
}
}
}
}
void checkwinO(vector<int>&board){
vector<int>pos;
vector<int>magicsquare = {8,3,4,1,5,9,6,7,2};
vector<int>valstore;
for(int i=0;i<9;i++){
if(board[i] == 5){
pos.push_back(i);
}
}
for(int i=0;i<9;i++)
{
for(int j=0;j<pos.size();j++)
{
if(i == pos[j])
{
valstore.push_back(magicsquare[i]);
}
}
}
vector<int>results;
for (int i = 0; i < valstore.size(); i++) {
for (int j = i + 1; j < valstore.size(); j++) {
for (int k = i + 2; k < valstore.size(); k++) {
if((valstore[i] + valstore[j] + valstore[k]) == 15){
cout << endl;
cout << "player 2 wins " << endl;
exit(1);
}
}
}
}
}
void usermove();
void computermove(){
if(turn == 1){
go(0);
display();
usermove();
}
else if(turn == 2){
if(board[4] == 2){
go(4);
}
else{
go(0);
}
display();
usermove();
}
else if(turn == 3){
if(board[8] == 2){
go(8);
}
else{
go(2);
}
display();
usermove();
}
else if(turn == 4){
if(posswinX(board)!=-1){
go(posswinX(board));
}
else{
go(make2(board));
}
display();
usermove();
}
else if(turn == 5){
if(posswinX(board)!=-1){
go(posswinX(board));
}
else if(posswinO(board)!=-1){
go(posswinO(board));
}
else if(board[6]==2){
go(6);
}
else{
go(2);
}
display();
checkwinX(board);
usermove();
}
else if(turn == 6){
if(posswinO(board)!=-1){
go(posswinO(board));
}
else if(posswinX(board)!=-1){
go(posswinX(board));
}
else{
go(make2(board));
}
display();
checkwinO(board);
usermove();
}
else if(turn == 7){
if(posswinX(board)!=-1){
go(posswinX(board));
}
else if(posswinO(board)!=-1){
go(posswinO(board));
}
else{
go(make2(board));
}
display();
checkwinX(board);
usermove();
}
else if(turn == 8){
if(posswinO(board)!=-1){
go(posswinO(board));
}
else if(posswinX(board)!=-1){
go(posswinX(board));
}
else{
go(make2(board));
}
display();
checkwinO(board);
usermove();
}
else if(turn == 9){
if(posswinX(board)!=-1){
go(posswinX(board));
}
else if(posswinO(board)!=-1){
go(posswinO(board));
}
else{
go(make2(board));
}
display();
checkwinX(board);
}
cout << endl;
cout << "game draws" << endl;
exit(1);
}
void usermove(){
bool valid;
int n;
cout << endl;
cout << "enter the block number for your move : " << endl;
cin >> n;
do{
if(turn <= 9 && board[n-1] == 2){
valid = true;
go(n-1);
display();
checkwinX(board);
checkwinO(board);
cout << endl;
cout << endl;
cout << "computer's move" << endl;
computermove();
}
else if(board[n-1] != 2){
valid = true;
cout << "invalid move : " << endl;
cout << "enter the block number for your move : " << endl;
cin >> n;
}
else if(turn > 9){
valid = false;
cout << "game draws" << endl;
}
}while(valid);
}
int main(){
cout << "Your turn: 1. First or 2. Second" << endl;
int myturn;
cin >> myturn;
if(myturn == 1){
usermove();
}
else if(myturn == 2){
computermove();
}
return 0;
}