/*	Filename:		Mapping.cpp
	Description:	Implementation of a class representing the mapping of vertices between two graphs
					******NOTE******: no longer needed with current implementation
	Author:			Tien Huynh
*/

#include "Mapping.h"


ParaMODAImpl::Mapping::Mapping()
{
   this->Id = -1;
}

ParaMODAImpl::Mapping::Mapping(const Mapping & mapping)
{
   this->Id = mapping.Id;
   this->SubGraphEdgeCount = mapping.SubGraphEdgeCount;
   this->Function = mapping.Function;
}


ParaMODAImpl::Mapping::Mapping(tsl::hopscotch_map<int, int> function)
{
   this->Id = -1;
   this->Function = function;
}

ParaMODAImpl::Mapping::~Mapping()
{
}


//Overload equal operator for comparing Mapping objects
//	  all <key,value> pairs must be the same in both objects
bool ParaMODAImpl::Mapping::operator==(const Mapping & other) const
{
   if (this->Id >= 0 || other.Id >= 0)
	  return this->Id == other.Id;

   if (this->Function.size() != other.Function.size())
	  return false;

   for (auto const& itr : this->Function)
   {
	   try
	   {
		   if (itr.second != other.getFunction().at(itr.first))
			   return false;
	   }
	   catch (out_of_range)
	   {
		   return false;
	   }
   }
   return true;
}


string ParaMODAImpl::Mapping::GetMappedNodes()
{
   string result = "";
   if (this->Function.size())
   {
	   tsl::hopscotch_map<int, int>::iterator itr = this->Function.begin();
	  result += to_string((itr++)->second);
	  for (; itr != this->Function.end(); itr++)
	  {
		 result += '-' + to_string(itr->second);
	  }
   }
   return result;
}


//overload output operators
ostream & ParaMODAImpl::operator<<(ostream & outStream, const Mapping & data)
{
   string h = "";
   string g = "";

   if (data.getFunction().size())
   {
	  h += "[";
	  g += " => [";

	  for (auto const& itr : data.getFunction())
	  {
		 h += to_string(itr.first) + '-';
		 g += to_string(itr.second) + '-';
	  }
	  h.pop_back();
	  h += "]";
	  g.pop_back();
	  g += "]\n";
   }
   outStream << h << g;
   return outStream;
}
