#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>

int board_rows = 100;
int board_cols = 100;

struct RGB
{
    double r = 1; //0 - 1
    double g = 1; //0 - 1
    double b = 1; //0 - 1

    double operator - (const RGB& rgb) const
    {
        return std::fabs(rgb.r - r)
            + std::fabs(rgb.g - g)
            + std::fabs(rgb.b - b);
    }
};

struct Box
{
    RGB  rgb;

    int left_up_x = 0;
    int left_up_y = 0;
    int right_down_x = 0;
    int right_down_y = 0;

    double randZeroToOne()
    {
        return (double) rand()/RAND_MAX;
    }

    double getColorDelta(double scale)
    {
        //return (randZeroToOne()-0.5)*0.1;
        return (randZeroToOne()-0.5)*0.2*scale;
    }

    double getPositionDelta(double scale)
    {
        //return (randZeroToOne()-0.5)*10;
        return (randZeroToOne()-0.5)*20*scale;
    }

    Box mutate(double scale)
    {
        Box box;
        box.rgb = rgb;
        box.left_up_x = left_up_x;
        box.left_up_y = left_up_y;
        box.right_down_x = right_down_x;
        box.right_down_y = right_down_y;

        double c_delta = getColorDelta(scale);;

        while(box.rgb.r + c_delta >1 || box.rgb.r + c_delta <0){
            c_delta = getColorDelta(scale);;
        }
        box.rgb.r += c_delta;

        c_delta = getColorDelta(scale);;
        while(box.rgb.g + c_delta >1 || box.rgb.g + c_delta <0){
            c_delta = getColorDelta(scale);;
        }
        box.rgb.g += c_delta;

        c_delta = getColorDelta(scale);;
        while(box.rgb.b + c_delta >1 || box.rgb.b + c_delta <0){
            c_delta = getColorDelta(scale);;
        }
        box.rgb.b += c_delta;

        //std::cout<<"box.left_up_x = "<<box.left_up_x<<std::endl;
        int pos_delta = getPositionDelta(scale);
        while(box.left_up_x+pos_delta >= board_rows-1 || box.left_up_x+pos_delta <0)
            pos_delta = getPositionDelta(scale);
        box.left_up_x += pos_delta;

        //std::cout<<"box.left_up_y = "<<box.left_up_y<<std::endl;

        pos_delta = getPositionDelta(scale);
        while(box.left_up_y+pos_delta >= board_cols-1 || box.left_up_y+pos_delta <0)
            pos_delta = getPositionDelta(scale);
        box.left_up_y += pos_delta;


        //std::cout<<"box.right_down_x = "<<box.right_down_x<<std::endl;
        pos_delta = getPositionDelta(scale);
        while(box.right_down_x+pos_delta>= board_rows || box.right_down_x+pos_delta <= box.left_up_x)
        {
            pos_delta = getPositionDelta(scale);
            //std::cout<<"-----"<<std::endl;
            //std::cout<<"pos_delta = "<<pos_delta<<std::endl;
            //std::cout<<"box.right_down_x = "<<box.right_down_x<<std::endl;
            //std::cout<<"box.right_down_x+pos_delta = "<<(box.right_down_x+pos_delta)<<std::endl;
            //std::cout<<"box.left_up_x = "<<(box.left_up_x)<<std::endl;
            //std::cout<<"board_rows = "<<board_rows<<std::endl;
        }
        box.right_down_x += pos_delta;

        //std::cout<<"box.right_down_y = "<<box.right_down_y<<std::endl;

        pos_delta = getPositionDelta(scale);
        while(box.right_down_y + pos_delta>= board_cols || box.right_down_y + pos_delta <= box.left_up_y)
        {
            pos_delta = getPositionDelta(scale);
            //std::cout<<"pos_delta = "<<pos_delta<<std::endl;
            //std::cout<<"box.right_down_y = "<<box.right_down_y<<std::endl;
        }
        box.right_down_y += pos_delta;

        return box;
    }

    void print()
    {
        std::cout<<" rgb = ["<<rgb.r<<","<<rgb.g<<","<<rgb.b<<"]"<<std::endl;
        std::cout<<" left_up = ["<<left_up_x<<","<<left_up_y<<"]"<<std::endl;
        std::cout<<" right_down = ["<<right_down_x<<","<<right_down_y<<"]"<<std::endl;
    }
};


struct Board
{
    std::vector<std::vector<RGB>> data;
    Board(int rows, int cols)
    {

        for (int i = 0 ; i < rows ; i++)
        {
            std::vector<RGB> row;
            for(int j = 0 ; j < cols ; j++)
            {
                row.push_back(RGB());
            }
            data.push_back(row);
        }	
    }

    void saveBoard(const std::string& file_name)
    {
        // write out image
        std::ofstream myfile;
        myfile.open (file_name);
        for (int i = 0 ; i < data.size(); i++)
        {
            for(int j = 0 ; j < data[0].size(); j++)
            {
                myfile << i<<","<<j<<","<<data[i][j].r<<","<<data[i][j].g<<","<<data[i][j].b<<"\n";
            }
        }	
        myfile.close();
    }
};

void drawBoxOnBoard(const Box& box, Board& board)
{
    for(int i = box.left_up_y ; i<= box.right_down_y ; i++)
    {
        for(int j = box.left_up_x ; j<= box.right_down_x ; j++)
        {
            if(i<0 || i >= board_rows || j<0 || j>=board_cols)
            {
                std::cout<<"i = "<<i<<" j = "<<j<<std::endl;
                std::cin.get();
            }
            board.data[i][j].r = std::max(0.0, board.data[i][j].r -  box.rgb.r);
            board.data[i][j].g = std::max(0.0, board.data[i][j].g -  box.rgb.g);
            board.data[i][j].b = std::max(0.0, board.data[i][j].b -  box.rgb.b);
        }
    }
}

Board getTargetBoard(int rows, int cols)
{
    Board board(rows, cols);

    Box box;
    box.rgb.r = 0;
    box.rgb.g = 0;
    box.rgb.b = 0.5;
    box.left_up_x = 30;
    box.left_up_y = 30;
    box.right_down_x = 80;
    box.right_down_y = 80;

    drawBoxOnBoard(box, board);

    box.rgb.r = 0.4;
    box.rgb.g = 0;
    box.rgb.b = 0;
    box.left_up_x = 10;
    box.left_up_y = 10;
    box.right_down_x = 40;
    box.right_down_y = 60;

    drawBoxOnBoard(box, board);

    box.rgb.r = 0;
    box.rgb.g = 0.7;
    box.rgb.b = 0;
    box.left_up_x = 50;
    box.left_up_y = 40;
    box.right_down_x = 90;
    box.right_down_y = 60;

    drawBoxOnBoard(box, board);

    return board;
}




struct Entity
{
    int num_box = 3;
    std::vector<Box> box_vec;
    Entity()
    {
        for(int i = 0 ; i < num_box ; i++)
        {
            Box box;
            box.rgb.r = 0.2;
            box.rgb.g = 0.2;
            box.rgb.b = 0.2;
            box.left_up_x = 40;
            box.left_up_y = 40;
            box.right_down_x = 60;
            box.right_down_y = 60;

            Box mutated_box = box.mutate(1);
            box_vec.push_back(mutated_box);
        }
    }

    Entity(const Entity& entity)
    {
        for(int i = 0 ; i < entity.box_vec.size(); i++)
        {
            box_vec.push_back(entity.box_vec[i]);
        }
    }

    Entity mutate(double scale)
    {
        Entity new_entity(*this);
        for(int i = 0 ; i < new_entity.box_vec.size(); i++)
        {
            new_entity.box_vec[i] = new_entity.box_vec[i].mutate(scale);
        }

        return new_entity;
    }

    Board getBoard()
    {
        //std::cout<<"getBoard 1"<<std::endl; 
        Board board(board_rows, board_cols);
        //std::cout<<"board size = "<<board.data[0].size()<<std::endl;
        for(int i = 0 ; i < box_vec.size() ; i ++)
        {
            //std::cout<<"Drawing ["<<i<<"]"<<std::endl;
            //box_vec[i].print();
            drawBoxOnBoard(box_vec[i], board);
        }
        //std::cout<<"getBoard 2"<<std::endl; 
        //std::cout<<"board size 2 = "<<board.data[0].size()<<std::endl;

        return board;
    }

    void saveBoard(const std::string& file_name)
    {
        getBoard().saveBoard(file_name);
    }
};

double getError(const Board& b1, const Board& b2)
{
    double error = 0;
    for(int i = 0 ; i < b1.data.size() ; i++)
    {
        for(int j = 0 ; j < b1.data[0].size() ; j++)
        {
            error += std::fabs(b1.data[i][j] - b2.data[i][j]);
        }
    }

    return error;
}

bool sortPair(const std::pair<double, Entity> &a,
        const std::pair<double, Entity> &b)
{
    return (a.first< b.first);
}

int main(int ac, char** av)
{

    // initialize seed for rand()
    srand( (unsigned)time( NULL ) );

    std::cout<<"hello world"<<std::endl;
    Board board_target = getTargetBoard(board_rows, board_cols);

    board_target.saveBoard("example.bd");


    int num_survival = 3;
    int num_children_each_survival = 30;

    std::vector<Box> box_vec;
    std::vector<Entity> entity_vec;

    // add inital survivals
    for(int i = 0 ; i < num_survival ; i++)
    {
        entity_vec.push_back(Entity());
    }

    for(int iter = 0 ; iter < 10000 ; iter++)
    {
        std::cout<<"============="<<std::endl;
        std::cout<<"Iter = "<<iter<<std::endl;

        // survivals make children and each children mutate
        std::vector<Entity> child_vec;
        for(int i = 0 ; i < entity_vec.size(); i++)
        {
            child_vec.push_back(entity_vec[i]);
            for(int j = 0 ; j < num_children_each_survival ; j++)
            {
                Entity child = entity_vec[i].mutate(1);
                child_vec.push_back(child);
            }
            
            // big mutation
            for(int j = 0 ; j < num_children_each_survival ; j++)
            {
                Entity child = entity_vec[i].mutate(10);
                child_vec.push_back(child);
            }
        }

        // each child produce result
        std::vector<std::pair<double, Entity>> score_entity_vec;
        for(int i = 0 ; i < child_vec.size() ; i++)
        {
            double error = getError(board_target, child_vec[i].getBoard());
            score_entity_vec.push_back(std::make_pair(error, child_vec[i]));
            //std::cout<<"error = "<<error<<std::endl;
        }

        // keep the best ones and kill the rest.
        std::sort(score_entity_vec.begin(), score_entity_vec.end(), sortPair);
        entity_vec.clear();
        std::cout<<"Error = [";
        for(int i = 0 ; i < num_survival ; i++)
        {
            std::cout<<score_entity_vec[i].first<<", ";

            Entity entity = score_entity_vec[i].second;
            entity_vec.push_back(entity);

            if(iter%1000==0)
            {
                std::string file_name = "board_"+std::to_string(iter)+"_"+std::to_string(i)+".bd";
                entity.saveBoard(file_name);
            }

        }
        std::cout<<"]"<<std::endl;

    }

    std::cout<<"All iteration finished"<<std::endl;



    return 0;
};
