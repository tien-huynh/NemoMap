#pragma once
#include <string>
#include <iostream>
using namespace std;
namespace QuickGraph
{
	template <typename TVertex>
	class Edge
	{
	public:
		Edge();
		Edge(TVertex source, TVertex target);
		string toString();
		TVertex getSource() const;
		TVertex getTarget() const;
		bool Equals(Edge temp);
	private:
		TVertex source;
		TVertex target;

	};

	template<typename TVertex>
	inline Edge<TVertex>::Edge()
	{
		source = nullptr;
		target = nullptr;
	}

	template<typename TVertex>
	inline Edge<TVertex>::Edge(TVertex source, TVertex target)
	{
		this->source = source;
		this->target = target;
	}

	template<typename TVertex>
	inline string Edge<TVertex>::toString()
	{
		return to_string(getSource()) + "->" + to_string(getTarget());

	}

	template<typename TVertex>
	inline TVertex Edge<TVertex>::getSource() const
	{
		return source;
	}

	template<typename TVertex>
	inline TVertex Edge<TVertex>::getTarget() const
	{
		return target;
	}

	template<typename TVertex>
	inline bool Edge<TVertex>::Equals(Edge temp)
	{
		if (temp.getSource() == getSource() && temp.getTarget() == getTarget() ||
			temp.getSource() == getTarget() && temp.getTarget() == getSource())
			return true;
		else
			return false;
	}
}