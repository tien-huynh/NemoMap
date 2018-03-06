#include <type_traits>

using namespace QuickGraph::Collections;
using namespace QuickGraph;


	// I have no idea what all this is, 
	// I just pieced it together from google + stackoverflow
	template<typename TVertex, typename TEdge>
	using EdgeEqualityComparer = std::function<bool(TEdge edge, TVertex source, TVertex target)>;
	static_assert(std::is_base_of<IEdge<TVertex>, TEdge>::value, "");

	template<typename TVertex, typename TEdge>
	
	
	class UndirectedGraph : public IUndirectedGraph<TVertex, TEdge> 
	{
		static_assert(std::is_base_of<IEdge<TVertex>, TEdge>::value, "where TEdge : IEdge<TVertex>?");
	private:
		const bool allowParallelEdges = true;
		VertexEdgeDictionary<TVertex, TEdge> *const adjacentEdges;
		const EdgeEqualityComparer<TVertex, TEdge> edgeEqualityComparer;
		int edgeCount = 0;
		int edgeCapacity = 4;

	public:
		virtual ~UndirectedGraph()
		{
			delete adjacentEdges;
		}
		UndirectedGraph();

		UndirectedGraph() : UndirectedGraph(true)
		{
		}

		UndirectedGraph(bool allowParallelEdges) : allowParallelEdges(allowParallelEdges), edgeEqualityComparer(EdgeExtensions::GetUndirectedVertexEquality<TVertex, TEdge>())
		{
			this->edges2 = std::unordered_map<TVertex, std::vector<TVertex>>();
			
		}

		EdgeEqualityComparer<TVertex, TEdge> *getEdgeEqualityComparer() const
		{
			return this->edgeEqualityComparer;
		}

		int getEdgeCapacity() const
		{
			return this->edgeCapacity;
		}
		void setEdgeCapacity(const int &value)
		{
			this->edgeCapacity = value;
		}


		//using vectors to replace the ILists
		std::vector<TVertex> GetNeighbors(TVertex vertex)
		{
			std::vector<TVertex> adjEdges;
			if (this->edges2.TryGetValue(vertex, adjEdges))
			{
				return adjEdges;
			}
			return std::vector<TVertex>(0);
		}

		std::vector<TVertex> GetNodesSortedByDegree(int count)
		{
			//using unordered_maps to replace the dictionaries
			auto tempList = std::unordered_map<TVertex, int>(count);
			for (auto node : Vertices::Take(count))
			{
				tempList.emplace(node, this->AdjacentDegree(node));
			}

			auto listToReturn = std::vector<TVertex>(count);
			for (auto item : tempList.OrderByDescending([&](void *x)
			{
				x->Value;
			}))
			{
				listToReturn.push_back(item::Key);
			}

			tempList.clear();
			return listToReturn;
		}
		
		std::vector<int> GetDegreeSequence()
		{
			auto listToReturn = std::vector<int>(VertexCount);
			for (auto node : Vertices)
			{
				listToReturn.push_back(this->AdjacentDegree(node));
			}

			return listToReturn.OrderByDescending([&](void *x)
			{
				return x;
			})->ToArray();
		}

		UndirectedGraph<TVertex, TEdge> *Clone()
		{
			auto inputGraphClone = new UndirectedGraph<TVertex, TEdge>();
			for (auto edge : this->Edges2)
			{
				inputGraphClone->AddVerticesAndEdge(edge->Source, edge->Target);
			}
			return inputGraphClone;
		}

		bool getIsDirected() const
		{
			return false;
		}

		bool getAllowParallelEdges() const
		{
			return this->allowParallelEdges;
		}

		bool RemoveVertex(TVertex v)
		{
			this->ClearAdjacentEdges(v);
			return this->edges2->Remove(v);
		}

		void ClearAdjacentEdges(TVertex v)
		{
			std::vector<TVertex> ends(this->edges2[v]);
			this->edgeCount -= ends.size();
			for (auto end : ends)
			{
				std::vector<TVertex> otherEnds;
				if (this->edges2.TryGetValue(end, otherEnds))
				{
					otherEnds.Remove(v);
				}
			}
			ends.clear();
		}

	};
