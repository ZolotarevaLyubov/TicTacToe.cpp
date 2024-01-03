#include<iostream>
#include<array>
#include<vector>
using namespace std;

enum class game_values
{
 x_win,
 o_win,
 continue_game,
 tie
};

const bool print_tree = false;

void print_num(array<char, 9> field)
{
 char num = '1';
 int index;
 for(int i = 0; i < 3; i++)
 {
  for(int j = 0; j < 3; j++)
  {
   index = i * 3 + j;
   if(field.at(index) == ' ')
   {
    field.at(index) = num;
    cout<<num<< " ";
   }
   else
    {
     cout<<field.at(index)<<" ";
    }
    num++; 
  }
   cout<<endl;
 }
}

void print_arr(array<char, 9> field)
{
 int index;
 for(int i = 0; i < 3; i++)
 {
  for(int j = 0; j < 3; j++)
  {
   index = i * 3 + j;
   cout<<field.at(index)<<" "; 
  }
   cout<<endl;
 }
}

void print(vector<array<char, 9>> field)
{
 for(int i = 0; i < 3; i++)
 {
 for(int board = 0; board < field.size(); board++)
 {
 for(int j = 0; j < 3; j++)
 {
  cout<<field.at(board).at(i * 3 + j)<< " ";
 }
 cout<<" | ";
 }
 cout<<endl;
}
}
bool space(array<char, 9> field)
{
 
 for(int i = 0; i < 3; i++)
 {
  for(int j = 0; j < 3; j++)
  {
   if(field.at(i * 3 + j) == ' ')
   return 1;
  }
 }
 return 0;
}


vector<array<char,9>> moves(array<char, 9>field, char user)
{
 vector<array<char,9>>new_map;
 for(int i = 0; i < 3; i++)
 {
  for(int j = 0; j < 3; j++)
  {
   if(field.at(i * 3 + j) == ' ')
   {
    array<char, 9> new_field = field;
    new_field.at(i * 3 + j) = user;
    new_map.push_back(new_field); 
   }
  }
 }
 return new_map;
}

void print_vector(vector<array<char ,9>>new_field)
{
 for(auto i : new_field)

 {
  print_arr(i);
  cout<<endl; 
 }
 cout<<endl;
}


game_values exam(array<char, 9> field)

{

 
 char winners[] = {'o', 'x'};
 
 for(char winner : winners)
 {
 
  for(int i = 0; i < 3; i++)
  {
   if(field.at(i * 3 + 0) == winner && field.at(i * 3 + 1) == winner && field.at(i * 3 + 2) == winner)
   {
    return (winner == 'x')? game_values::x_win : game_values::o_win;
   }
   
   if(field.at(0 * 3 + i) == winner && field.at(1 * 3 + i) == winner && field.at(2 * 3 + i) == winner)
   {
    return (winner == 'x')? game_values::x_win : game_values::o_win; 
   }
  }
  
  if(field.at(0 * 3 + 0) == winner && field.at(1 * 3 + 1) == winner && field.at(2 * 3 + 2) == winner)
   {
   return (winner == 'x')? game_values::x_win : game_values::o_win; 
   }
  if(field.at(0 * 3 + 2) == winner && field.at(1 * 3 + 1) == winner && field.at(2 * 3 + 0) == winner)
   {
   return (winner == 'x')? game_values::x_win : game_values::o_win;
   } 
 }
 
 
 return space(field)? game_values::continue_game : game_values::tie;
 
}

void print_values(game_values state)
{
 switch (state)
 {
  case game_values::x_win:
   cout<<"x winner";
   break;
  case game_values::o_win:
   cout<<"o winner";
   break;
  case game_values::continue_game:
   cout<<"continue game";
   break;
  case game_values::tie:
   cout<<"tie";
   break;   
   
 }
}


//(x==1)? 42: 13


int max (vector<int> num)
{
 int max_num = num[0];
 
 for(int i = 0; i < num.size(); i++)
 {
  if(num[i] > max_num)
  {
   max_num = num[i];
  }
 }
 return max_num;
}

int min (vector<int> num)
{
 int min_num = num[0];
 
 for(int i = 0; i < num.size(); i++)
 {
  if(num[i] < min_num)
  {
   min_num = num[i];
  }
 }
 return min_num;
} 


void print_vector(vector<int>num)
{
 for(int i:num)
 {
  cout<<i<<"        ";
 }
 cout<<endl;
}

void print_trees(array<char, 9>field, int num, int depth)
{
 if(print_tree)
 {
  print_arr(field);
  cout<<"evaluation =  "<<num<< "  "<<"depth  "<<depth<<endl;
 }
}

//x - компьютер
//о - пользователь

void print_t(vector<array<char, 9>>new_map,vector<int> num, int depth)
{
  if(print_tree)
 {
  print(new_map);
 
  print_vector(num);
  cout<<"depth "<<depth<<endl;
 } 
}

int evaluation(array<char, 9> field, char user, int depth)
{
 game_values state = exam(field);
 
 if(state == game_values::x_win)
 {
 
  print_trees(field, 1, depth);
  return 1;
 }
 else if(state == game_values::o_win)
 {
 
  print_trees(field, -1, depth);
  return -1;
 }
 else if(state == game_values::tie)
 {

  print_trees(field, 0, depth);
  return 0;    
 }
 
 vector<array<char, 9>>new_map = moves(field, user);
 
 vector<int>num;
 for(auto m : new_map)
 {
  num.push_back(evaluation(m,(user == 'x')? 'o':'x', depth+1));
 }
 print_t(new_map, num, depth);
 return user == 'x'? max(num):min(num);
 }


//считает сумму всех возможных ходов, начиная от какой то доски
int count_moves(array<char, 9> field, char user, int depth)
{
 int count = 1;
 game_values state = exam(field);
 if(state == game_values::x_win || state == game_values::o_win || state == game_values::tie)
 {
  
  print_arr(field);
  cout<<depth<<endl;
  return count;
 }

 vector<array<char, 9>>new_map = moves(field, user);
 print(new_map);
 cout<<depth<<endl;
 //для каждой из порождённых досок посчитать сумму всех возможных ходов, начиная отт неё
 
 
 for(auto m : new_map)
 {
  //count++;
  count += count_moves(m,(user == 'x') ? 'o':'x', depth+1);  // x++ -> x=x+1
  
 }
 return count;
}

int get_user_move(array<char, 9> field)
{
 int move;
 bool valid_move = false;
 while(!valid_move)
 {
  cout<<"Enter the number of an empty cell"<<endl;
  cin>>move;
  if(move >= 1 && move <= 9 && field[move - 1] == ' ')
  {
   valid_move = true;
  }
  else
  {
   cout<<"Invalid move. Choose an empty cell."<<endl;
  }
 } 
 return move;
}

array<char, 9> best_move(array<char, 9> field, char user)//исправить
{
 vector<array<char, 9>> possible_moves = moves(field, user);
 array<char, 9> best = field;
 int best_score = -1;
  
 for(auto move : possible_moves)
 {
  int score = evaluation(move, (user == 'x')? 'o':'x', 1);
  
  if(best_score < score)
  {
   best_score = score;
   best = move;
  }
 }
 return best;
}

void copy_field(array<char, 9> field, array<char, 9>& new_field)
{
 
 for(int i = 0; i < 3; i++)
 {
  for(int j = 0; j < 3; j++)
  {
   int index = i * 3 + j;
   new_field.at(index) = field.at(index);
  }
 }
}

bool exam_win(game_values state)
{
 return state == game_values::o_win || state == game_values::x_win || state == game_values::tie;
}

int main()
{
 
 array<char, 9> field = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
 
 int user_move;
 print_num(field);
 cout<<endl;
 
 for(int i = 0; i < 9; i++ )
 {
  user_move = get_user_move(field);
  if(user_move >= 1 && user_move <= 9 &&field[user_move - 1] == ' ')
  {
   field[user_move - 1] = 'o';
  }
  else
   cout << "Error" <<endl;
  print_num(field);
  cout<<endl;
  
   game_values state = exam(field);
  
  if(exam_win(state))
  {
   print_values(state); 
   return 0;
  }
 
  
  array<char, 9> new_field = best_move(field, 'x');
  //field = new_field;
   copy_field(new_field, field); 
  
  
  print_num(new_field);
  cout<<endl;
  
  state = exam(field);
  print_values(state);
  
  state = exam(field);
  
  if(exam_win(state))
  { 
   print_values(state); 
   return 0;
  } 
 
 }
 cout<<endl;
 //print_vector(moves(field, 'x'));
 //print(moves(field, 'x'));
 
 //motion(field, 'x', 1);
 //int num = count_moves(field, 'x', 1);
 
 return 0;
}


