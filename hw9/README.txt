HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME:  Jerald Jacobs


COLLABORATORS AND OTHER RESOURCES:
www.cplusplus.com
Cavell Teng
Nick Curtis


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 6


AALGORITHM ANALYSIS: 

Assume v_0 vertices, e_0 edges, and t_0 triangles in the initial mesh,
k edges connected to each vertex (average or worst case),
reduced to t_final triangles using the -shortest criteria.
What is the overall order notation for the program?  Analyze the
separate compoenents of the program to justify your answer.


ALGORITHM ANALYSIS -- LINEAR: O(log v_0 * log t_0 * log e_0  * e_0)
The linear sweep searches through all the edges and determines which edge to collapse next after it is finished. This is very expensive because the order notation for just this part is O(e_0). So it multiplies the order notation by e_0.

ALGORITHM ANALYSIS -- PRIORITY QUEUE: O(log v_0 * log t_0 * log e_0)
The priority queue method determines the next edge to be collapsed simply by returning the top element on the priority queue tree which is very inexpensive. The order notation for this is only O(1) because it simply returns the first element in the vector. So it multiplies the order notation by 1, which changes nothing.


FOR BOTH LINEAR AND PRIORITY QUEUE, THIS APPLIES:
After it determines the edge to collapse, it must determine all of the triangles that are touching the edge. It then runs a loop through those triangles and removes that triangle and re adds the triangle with new vertices to the mesh (with the exception of the 2 triangles being removed). This has order notation O(log t_0).

Each time a triangle in that ^ loop (per edge) is updated (removed and re added), it re evaluates the vertices in the mesh which has order notation O(log v_0) since it has to erase from a set. Removing an edge has to .find() it in the map which has O(log e_0). So that gets multiplied onto the overall order notation.


ALGORITHM ANALYSIS -- IMPACT OF -preserve_area command line argument?
Do your answers above change with or without the -preserve_area
command line argument?  Describe.

Yes the answers will change with preserve area because the additional restriction requires a check that gets the area before and after it “collapses”. It checks getArea before and after and this adds to the order notation of the overall function.


TABLE SUMMARIZING RUN TIMES (linear and priority queue):

Target 150: 0m0.196s
Target 100: 0m0.205s
Target  50: 0m0.207s
Target  10: 0m0.210s
Dimension  10  10: 0m0.193s
Dimension  30  30: 0m0.284s
Dimension  50  50: 0m1.377s

Target 150: 0m0.206s
Target 100: 0m0.207s
Target  50: 0m0.214s
Target  10: 0m0.215s
Dimension  10  10: 0m0.200s
Dimension  30  30: 0m0.525s
Dimension  50  50: 0m1.179s




