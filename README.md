## Graph Coloring and Ordering Algorithm

The provided code implements a graph coloring algorithm and two ordering algorithms for a graph. The following functions and structures are used in the code.

### Functions

#### `Greedy`

The `Greedy` function implements a greedy coloring algorithm for a graph. It takes a graph `G`, an order array `Order`, and a colors array `Colors` as parameters. The algorithm assigns colors to the vertices of the graph sequentially, taking into account the colors of neighboring vertices to avoid collisions. It returns the maximum number of colors used.

#### `ColoringInfo`

The `ColoringInfo` function creates a `coloring_information` structure that stores information about the coloring performed on the graph. It takes the number of vertices `n` and the colors array `Color` as parameters. The `coloring_information` structure contains the total number of colors used, a matrix that groups vertices by colors, and an array that indicates the number of vertices for each color. It returns a pointer to the created structure.

#### `OddEvenOrder`

The `OddEvenOrder` function implements an ordering algorithm for the order array `Order` using the odd-even sort method. It takes the number of vertices `n`, the order array `Order`, and the colors array `Color` as parameters. The algorithm sorts the vertices so that vertices with odd colors precede vertices with even colors.

#### `JediOrder`

The `JediOrder` function implements an ordering algorithm for the order array `Order` using the Jedi sorting method. It takes the graph `G`, the order array `Order`, and the colors array `Color` as parameters. The algorithm calculates a metric called `F` for each color and then sorts the vertices based on this metric.

#### `main`

The `main` function is the main function of the program. It constructs a graph, assigns random colors to the vertices, and calls the `JediOrder` function to obtain the Jedi order of the vertices. It prints the result to the console.

### Structures

#### `coloring_information`

The `coloring_information` structure stores information about the coloring performed on the graph. It has the following fields:

- `count`: the total number of colors used.
- `same_color`: a matrix that groups vertices by colors.
- `counts`: an array that indicates the number of vertices for each color.

### Usage

To use the code, you need to include the header files `APIG23.h` and `APIP2.h`, which contain the declarations of the functions and structures used. Additionally, you need to link the program with the corresponding libraries.

To perform the coloring and obtain the Jedi order of a graph, follow these steps:

1. Construct the graph and define the number of vertices.
2. Assign colors to the vertices using the `Greedy` function.
3. Call the desired ordering function (`OddEvenOrder` or `JediOrder`) to obtain the desired vertex order.
4. Access the `coloring_information` structure to retrieve the coloring information.

Please note that the provided code is a template, and you may need to modify it or integrate it into your existing codebase to fit your specific requirements.

The code expects the input graph to be in the DIMACS format.