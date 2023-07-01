#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
#include<cmath>
const double pai=acos(-1);
//加减数乘
template <typename type>
class vec {
  public:
    type x, y;
  
    vec(){
        x = y = 0;
    }
    vec(type _x, type _y){
        x = _x;
        y = _y;
    }
    vec operator+(const vec& t){
        vec ret;
        ret.x = x + t.x;
        ret.y = y + t.y;
        return ret;
    }
    vec operator-(const vec& t){
        vec ret;
        ret.x = x - t.x;
        ret.y = y - t.y;
        return ret;
    }
    vec& operator+=(const vec& t){
        x += t.x;
        y += t.y;
        return *this;
    }
    vec& operator-=(const vec& t){
        x -= t.x;
        y -= t.y;
        return *this;
    }
    vec operator-(){
        vec ret;
        ret.x = -x;
        ret.y = -y;
        return ret;
    }
    vec operator*(type v){
        vec ret;
        ret.x = x * v;
        ret.y = y * v;
        return ret;
    }
    bool operator==(const vec& t){
        return x == t.x && y == t.y;
    }

    type operator&(const vec& t){
      return x*t.x+y*t.y;
    } 

    type operator|(const vec& t){
      return x*t.y-y*t.x;
    }

    //返回本向量模长
    type length(){
      return sqrt(x*x+y*y);
    }

    //将本向量旋转delta度（弧度制
    void turn(double delta){
      double angle=atan((double)y/x)+y>0?0:pai;
      type l=length();
      angle+=delta;
      x=l*cos(angle);
      y=l*sin(angle);
    }
};
#endif