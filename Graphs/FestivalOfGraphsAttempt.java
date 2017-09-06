  
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Stack;
import java.util.Deque;
import java.util.ArrayDeque;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

class FestivalOfGraphs
{
	private Graph g;
	
	public void init(String graphFile) 
	{
		System.out.println(graphFile);
		// open the file
		BufferedReader br = null;
		
		try
		{
			// open the file called "graph.txt"
			br = new BufferedReader(new FileReader(graphFile));
		
			// read the first line
			String line = br.readLine();	
			
			// convert the first line (a string) to an integer (numberOfVertices)
			Integer n = Integer.parseInt(line);
			
			g = new Graph(n);
		
			for (int fromVertex = 0; fromVertex < n; ++fromVertex)
			{
				line = br.readLine();
				if (line.length() > 0)
				{
					int pos = 0;
					while (line.indexOf("{", pos) > -1)
					{
						String sub = line.substring(line.indexOf("{", pos) + 1, line.indexOf("}", pos + 1));
						Integer toVertex = Integer.parseInt(sub.substring(0, sub.indexOf(",")));
						Integer weightOfEdge = Integer.parseInt(sub.substring(sub.indexOf(",") + 1, sub.length()));
						pos = line.indexOf("}", pos + 1);
						if (!g.hasEdge(fromVertex, toVertex))
							g.addEdge(fromVertex, toVertex, weightOfEdge);
					}	
				}	
			}
		}
		catch (FileNotFoundException ex) {
			// handle FileNotFoundException
			System.out.println("No such file as " + graphFile + " in your directory");
		}
		catch (IOException ex) {
			// handle IOException
			System.out.println("Ran into problems processing " + graphFile);
		}
		finally {
			if (br != null) {
				try {
					br.close();
				}
				catch (IOException ex) {
					// handle IOException
					System.out.println("Ran into unrecoverable problems processing " + graphFile);
				}
			}
		}
		
	}
	
	public List<Integer> DepthFirstList(Integer v)
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		
		toExplore.push(v);
		visited.add(v);
		
		while(toExplore.isEmpty() != true)
		{
			int n = toExplore.removeFirst();
			vertices.add(n);
			
			if(visited.contains(n) == false)
				continue;
				
			for(Integer i: g.getAdjList(n).keySet())
			{
				if(visited.contains(i) == false)
				{
					toExplore.push(i);
					visited.add(i);
				}
			}
		}
		return vertices;
	}
	
	public List<Integer> BreadthFirstList(Integer v) 
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		
		toExplore.push(v);
		visited.add(v);

		while(toExplore.isEmpty() != true){
			int n = toExplore.removeLast();
			vertices.add(n);

			if (visited.contains(n) == false)
				continue;

			for (Integer i: g.getAdjList(n).keySet())
			{
				if (visited.contains(i) == false)
				{
					toExplore.push(i);
					visited.add(i);
				}
			}	
		}
		return vertices;
	}

	
	public Graph DepthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		
		toExplore.push(v);
		visited.add(v);
		int counter = 0;
		int buffer = 0;

		while(toExplore.isEmpty() != true)
		{
			Integer n = toExplore.removeFirst();

			if (counter != 0)
			{
				int backTrack = 1;

				while (!g.hasEdge(buffer,n))
				{
					buffer = visited.get(visited.size() - backTrack);
					backTrack++;
				}

				t.addEdge(buffer, n, g.getEdgeWeight(buffer, n));
			}

			if (visited.contains(n) == false)
				continue;

			buffer = n;

			for (Integer i: g.getAdjList(n).keySet())
			{
				if (visited.contains(i) == false)
				{
					toExplore.push(i); 
					visited.add(i);
				}
			}	
			counter++;
		}
		return t;
	}
	
	
	public Graph BreadthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		
		toExplore.push(v);
		visited.add(v);

		while(toExplore.isEmpty() == false)
		{
			int n = toExplore.removeFirst();

			if (visited.contains(n) == false)
				continue;

			for (Integer i: g.getAdjList(n).keySet())
			{
				if (visited.contains(i) == false)
				{
					toExplore.push(i); 
					visited.add(i);
					t.addEdge(n, i, g.getEdgeWeight(n,i));
				}
			}	
		}
		return t;
	}

	List<String> DijkstrasShortestPath(Integer t)
	{
		List<Integer> initialized = new ArrayList<Integer>();
		List<Integer> pathWeights = new ArrayList<Integer>();
		List<String> prettyWeights = new ArrayList<String>();
		
		Set<Integer> vertexSet = new HashSet<Integer>();
		
		return prettyWeights;
	}
	
	public Graph PrimsAlgorithm(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		return t;
	}
	
	
}

