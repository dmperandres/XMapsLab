#include "random.h"

long int _random_normal::Counter=_random_constant::RANDOM_CONSTANT;
long int _random_uniform_int::Counter=_random_constant::RANDOM_CONSTANT;
long int _random_uniform_double::Counter=_random_constant::RANDOM_CONSTANT;

_random_normal::_random_normal()
{
  _random_normal::Counter=_random_constant::RANDOM_CONSTANT;
}

_random_normal::_random_normal(double Mean, double Stddev, double Min1, double Max1):
      Distribution(Mean, Stddev)
{
  if (Min1<=Max1){
    Counter=_random_constant::RANDOM_CONSTANT;
    Min=Min1;
    Max=Max1;
  }
  else std::cout << "Error:_random_normal: Min > Max " << std::endl;
}

void _random_normal::init(double Mean, double Stddev, double Min1, double Max1){
    if (Min1<=Max1){
      Distribution.param(std::normal_distribution<double>::param_type(Mean,Stddev));
      Min=Min1;
      Max=Max1;
    }
    else std::cout << "Error:_random_normal: Min > Max " << std::endl;
  };

void	_random_normal::seed(){
    Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
    Generator.seed(Seed);
    Generator.discard(700000);
    Counter+=Seed;
  }

void	_random_normal::set_seed(long int Seed1){
    Seed=Seed1;
    Generator.seed((unsigned int) Seed);
    Generator.discard(700000);
  }

long int _random_normal::get_seed(){return Seed;}

void	_random_normal::save_seed(){
    Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
    Seed=(long int) std::random_device{}()+Counter;
    Counter+=Seed;
  }

void  _random_normal::load_seed(){
    Generator.seed((unsigned int) Seed);
    Generator.discard(700000);
    Distribution.reset();
  }

double _random_normal::value(){
    do{
      Value=Distribution(Generator);
    } while (Value<Min || Value>Max);
    return Value;
  }

_random_uniform_int::_random_uniform_int()
{
  Counter=_random_constant::RANDOM_CONSTANT;
}

_random_uniform_int::_random_uniform_int(int Min1,int Max1)
{
  if (Min1<=Max1){
    Counter=_random_constant::RANDOM_CONSTANT;
    Distribution.param(std::uniform_int_distribution<int>::param_type(Min1,Max1));
  }
  else std::cout << "Error:_random_uniform_int: Min > Max " << std::endl;
}

void _random_uniform_int::init(int Min1,int Max1)
{
  if (Min1<=Max1){
    Distribution.param(std::uniform_int_distribution<int>::param_type(Min1,Max1));
  }
  else std::cout << "Error:_random_uniform_int: Min > Max " << std::endl;
}

void _random_uniform_int::seed()
{
  Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
  Generator.seed(Seed);
  Generator.discard(700000);
  Counter+=Seed;
}

void _random_uniform_int::set_seed(long int Seed1)
{
  Seed=Seed1;
  Generator.seed((unsigned int) Seed);
  Generator.discard(700000);
}

long int _random_uniform_int::get_seed()
{
  return Seed;
};

void _random_uniform_int::save_seed()
{
  Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
  Seed=(long int) std::random_device{}()+Counter;
  Counter+=Seed;
}

void _random_uniform_int::load_seed()
{
  Generator.seed((unsigned int) Seed);
  Generator.discard(700000);
  Distribution.reset();
}

int _random_uniform_int::value()
{
  return Distribution(Generator);
}

_random_uniform_double::_random_uniform_double()
{
  Counter=_random_constant::RANDOM_CONSTANT;
}

_random_uniform_double::_random_uniform_double(double Min1,double Max1)
{
  if (Min1<=Max1){
    Counter=_random_constant::RANDOM_CONSTANT;
    Distribution.param(std::uniform_real_distribution<double>::param_type(Min1,Max1));
  }
  else std::cout << "Error:_random_uniform_double: Min > Max " << std::endl;
}

void _random_uniform_double::init(double Min1,double Max1)
{
  if (Min1<=Max1){
    Distribution.param(std::uniform_real_distribution<double>::param_type(Min1,Max1));
  }
  else std::cout << "Error:_random_uniform_double: Min > Max " << std::endl;
}

void _random_uniform_double::seed()
{
  Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
  Generator.seed(Seed);
  Generator.discard(700000);
  Counter+=Seed;
}

void _random_uniform_double::set_seed(long int Seed1)
{
  Seed=Seed1;
  Generator.seed((unsigned int) Seed);
  Generator.discard(700000);
}

long int _random_uniform_double::get_seed()
{
  return Seed;
};

void _random_uniform_double::save_seed()
{
  Seed= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()+Counter;
  Seed=(long int) std::random_device{}()+Counter;
  Counter+=Seed;
}

void _random_uniform_double::load_seed()
{
  Generator.seed((unsigned int) Seed);
  Generator.discard(700000);
  Distribution.reset();
}

double _random_uniform_double::value()
{
  return Distribution(Generator);
}

