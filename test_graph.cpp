//
//  test_graph_example.cpp
//  CS 271 Graph Project: Example Test File
//
//  Created by Dr. Stacey Truex
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
        infile.close();
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string, string> *G)
{
    try
    {
        // C1: Default test, return pointer to valid node and test its data
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"S\"" << endl;
        }
        
        // C2: Test for key that does not exist
        if (G->get("A") != nullptr)
        {
            cout << "Incorrect result getting non-existent vertex \"A\"" << endl;
        }
        
        // C3: Test for srtring-integer key (non-existent)
        if (G->get("123") != nullptr)
        {
            cout << "Incorrect result getting non-existent vertex with string key" << endl;
        }
        
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_reachable(Graph<string, string> *G)
{
    try
    {
        // C1: Default reachable test, see if two simple vertices are reachable
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        // C2: Cycle
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        // C4: Check if vertex is rechable to non-existent vertex
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
        // C5: Check if vertex from one side of T is reachable to vertex on otherside of T
        if (G->reachable("R", "X"))
        {
            cout << "Incorrectly identified vertex \"X\" as reachable from \"R\"" << endl;
        }
        // C6: Check if vertex in a cycle can reach vertex outside of a cycle
        if (G->reachable("X","T"))
        {
            cout << "Incorrectly identified vertex \"T\" as reachable from \"X\"" << endl;
        }
        // C7: Check if non-existant vertex can reach non-existant vertex
        if (G->reachable("A", "123"))
        {
            cout << "Incorrectly identified non-existant vertex \"123\" as reachable from non-existant vertex \"A\"" << endl;
        }
        // C8: Check if non-existant vertex can reach existing vertex
        if (G->reachable("A", "S"))
        {
            cout << "Incorrectly identified vertex \"S\" as reachable from non-existant vertex \"A\"" << endl;
        }
        // C9: Check if same node is reachable to itself (valid reachability), in a cycle
        if (!G->reachable("R","R"))
        {
            cout << "Incorrectly identified vertex \"R\" as unreachable from \"R\"" << endl;
        }
        // C10: Check if same node is reachable to itself (valid reachability), in a cycle
        if (!G->reachable("X","X"))
        {
            cout << "Incorrectly identified vertex \"X\" as unreachable from \"X\"" << endl;
        }
        // C11: Check if same node is reachable to itself (unvalid reachability), not in a cycle
        if (G->reachable("T","T"))
        {
            cout << "Incorrectly identified vertex \"T\" as reachable from \"T\"" << endl;
        }
        // C12: Checking reachables from T
        if (!G->reachable("T","X"))
        {
            cout << "Incorrectly identified vertex \"X\" as unreachable from \"T\"" << endl;
        }
        if (!G->reachable("T","V"))
        {
            cout << "Incorrectly identified vertex \"V\" as unreachable from \"T\"" << endl;
        }

    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string, string> *G)
{
    try
    {
        // C1: BFS on T
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
        // C2: BFS on S
        G->bfs("S");
        string vertices_S[3] = {"V", "R", "S"};
        int distances_S[3] = {2, 1, 0};
        for (int i = 0; i < 3; i++)
        {
            if (G->get(vertices_S[i]) == nullptr || G->get(vertices_S[i])->distance != distances_S[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_S[i] << " should have distance " << distances_S[i] << " from source vertex \"s\"" << endl;
            }
        }
        // C3: BFS on V
        G->bfs("V");
        string vertices_V[3] = {"S", "R", "V"};
        int distances_V[3] = {1, 2, 0};
        for (int i = 0; i < 3; i++)
        {
            if (G->get(vertices_V[i]) == nullptr || G->get(vertices_V[i])->distance != distances_V[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_V[i] << " should have distance " << distances_V[i] << " from source vertex \"v\"" << endl;
            }
        }
        // C4: BFS on R
        G->bfs("R");
        string vertices_R[3] = {"V", "S", "R"};
        int distances_R[3] = {1, 2, 0};
        for (int i = 0; i < 3; i++)
        {
            if (G->get(vertices_R[i]) == nullptr || G->get(vertices_R[i])->distance != distances_R[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_R[i] << " should have distance " << distances_R[i] << " from source vertex \"r\"" << endl;
            }
        }
        // C5: BFS on U
        G->bfs("U");
        string vertices_U[4] = {"Y", "W", "X", "U"};
        int distances_U[4] = {1, 2, 3, 0};
        for (int i = 0; i < 4; i++)
        {
            if (G->get(vertices_U[i]) == nullptr || G->get(vertices_U[i])->distance != distances_U[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_U[i] << " should have distance " << distances_U[i] << " from source vertex \"u\"" << endl;
            }
        }
        // C6: BFS on Y
        G->bfs("Y");
        string vertices_Y[4] = {"W", "X", "U", "Y"};
        int distances_Y[4] = {1, 2, 3, 0};
        for (int i = 0; i < 4; i++)
        {
            if (G->get(vertices_Y[i]) == nullptr || G->get(vertices_Y[i])->distance != distances_Y[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_Y[i] << " should have distance " << distances_Y[i] << " from source vertex \"y\"" << endl;
            }
        }
        // C7: BFS on W
        G->bfs("W");
        string vertices_W[4] = {"U", "Y", "W", "X"};
        int distances_W[4] = {2, 3, 0, 1};
        for (int i = 0; i < 4; i++)
        {
            if (G->get(vertices_W[i]) == nullptr || G->get(vertices_W[i])->distance != distances_W[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices_W[i] << " should have distance " << distances_W[i] << " from source vertex \"w\"" << endl;
            }
        }
        // C8: BFS on X
        G->bfs("X");
        string vertices_X[4] = {"Y", "W", "X", "U"};
        int distances_X[4] = {2, 3, 0, 1};
        for (int i = 0; i < 4; i++)
        {
            if (G->get(vertices_X[i]) == nullptr || G->get(vertices_X[i])->distance != distances_X[i]){
                cout << "Incorrect bfs result. Vertex " << vertices_X[i] << " should have distance " << distances_X[i] << " from source vertex \"x\"" << endl;
            }
        }
        
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_print_path(Graph<string, string> *G)
{
    try
    {
        // C1: Path from T
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }

        // C2: Non existent path
        stringstream empty_buffer;
        streambuf *empty_prevbuf = cout.rdbuf(empty_buffer.rdbuf());
        G->print_path("V", "T");
        cout.rdbuf(empty_prevbuf);
        if (empty_buffer.str() != "")
        {
            cout << "Incorrect path from vertex \"V\" to vertex \"T\". Expected nothing but got : " << empty_buffer.str() << endl;
        }

        // C3: Vertex to itself S -> S
        stringstream S_S_buffer;
        streambuf *S_S_prevbuf = cout.rdbuf(S_S_buffer.rdbuf());
        G->print_path("S", "S");
        cout.rdbuf(S_S_prevbuf);
        if (S_S_buffer.str() != "S")
        {
            cout << "Incorrect path from vertex \"S\" to vertex \"S\". Expected 'S' but got : " << S_S_buffer.str() << endl;
        }

        // C4: Path from T to X (should be shortest path)
        stringstream T_X_buffer;
        streambuf *T_X_prevbuf = cout.rdbuf(T_X_buffer.rdbuf());
        G->print_path("T", "X");
        cout.rdbuf(T_X_prevbuf);
        if (T_X_buffer.str() != "T -> W -> X")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"X\". Expected T -> W -> X but got : " << T_X_buffer.str() << endl;
        }
        
        // C5: Almost complete path
        stringstream X_W_buffer;
        streambuf *X_W_prevbuf = cout.rdbuf(X_W_buffer.rdbuf());
        G->print_path("X", "W");
        cout.rdbuf(X_W_prevbuf);
        if (X_W_buffer.str() != "X -> U -> Y -> W")
        {
            cout << "Incorrect path from vertex \"X\" to vertex \"W\". Expected X -> U -> Y -> W but got : " << X_W_buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}

int main()
{

    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_get(G);
    test_reachable(G);
    test_bfs(G);
    test_print_path(G);
    test_edge_class(G);
    test_bfs_tree(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}