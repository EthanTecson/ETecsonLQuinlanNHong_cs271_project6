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
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
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
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
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

    }
    //     // vector<string> keys = {"A", "B"};
    //     // vector<string> data = {"DataA", "DataB"};
    //     // vector<vector<string>> edges = {{"B"}, {}};
    //     // Graph<string, string> G(keys, data, edges);
    //     // stringstream buffer;
    //     // streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    //     // G.bfs_tree("A");
    //     // cout.rdbuf(prevbuf);
    //     // if (buffer.str() != "A\nB")
    //     // {
    //     //     cout << "Incorrect bfs tree. Expected : \nA\nB\nbut got :\n"
    //     //          << buffer.str() << endl;
    //     // }
    // }
    // // Test case 1: Graph with only one node
    // try
    // {
    //     vector<string> keys = {"A"};
    //     vector<string> data = {"DataA"};
    //     vector<vector<string>> edges = {{}};
    //     Graph<string, string> G(keys, data, edges);
    //     stringstream buffer;
    //     streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    //     G.bfs_tree("A");
    //     cout.rdbuf(prevbuf);
    //     if (buffer.str() != "A")
    //     {
    //         cout << "Incorrect bfs tree. Expected : \nA\nbut got :\n"
    //              << buffer.str() << endl;
    //     }
    
    // }

    //  // Test case 2: Graph with two connected nodes
    // try
    // {
    //     vector<string> keys = {"A", "B"};
    //     vector<string> data = {"DataA", "DataB"};
    //     vector<vector<string>> edges = {{"B"}, {}};
    //     Graph<string, string> G(keys, data, edges);
    //     stringstream buffer;
    //     streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    //     G.bfs_tree("A");
    //     cout.rdbuf(prevbuf);
    //     if (buffer.str() != "A\nB")
    //     {
    //         cout << "Incorrect bfs tree. Expected : \nA\nB\nbut got :\n"
    //              << buffer.str() << endl;
    //     }
    // }

    // // Test case 3: Graph with multiple nodes and edges
    // try
    // {
    //     vector<string> keys = {"A", "B", "C", "D"};
    //     vector<string> data = {"DataA", "DataB", "DataC", "DataD"};
    //     vector<vector<string>> edges = {{"B", "C"}, {"D"}, {}, {}};
    //     Graph<string, string> G(keys, data, edges);
    //     stringstream buffer;
    //     streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    //     G.bfs_tree("A");
    //     cout.rdbuf(prevbuf);
    //     if (buffer.str() != "A\nB C\nD")
    //     {
    //         cout << "Incorrect bfs tree. Expected : \nA\nB C\nD\nbut got :\n"
    //              << buffer.str() << endl;
    //     }
    // }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}


// void test_print_path(Graph<string, string> *G)
// {
//     try
//     {
//         stringstream buffer;
//         streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
//         G->print_path("T", "V");
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "T -> S -> R -> V")
//         {
//             cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
//         }
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing print path : " << e.what() << endl;
//     }
// }

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

// void test_bfs_tree(Graph<string, string> *G)
// {
//     try
//     {
//         stringstream buffer;
//         streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
//         G->bfs_tree("T");
//         cout.rdbuf(prevbuf);
//         if (buffer.str() != "T\nS U W\nR Y X\nV")
//         {
//             cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
//                  << buffer.str() << endl;
//         }


        
//         // Test case 2: Graph with 2 connected nodes
//         vector<string> keys2 = {"A", "B"};
//         vector<string> data2 = {"DataA", "DataB"};
//         vector<vector<string>> edges2 = {{"B"}, {}};
//         Graph<string, string> H(keys2, data2, edges2);
//         stringstream buffer2;
//         streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
//         H->bfs_tree("A");
//         cout.rdbuf(prevbuf2);
//         if (buffer2.str() != "A\nB")
//         {
//             cout << "Incorrect bfs tree. Expected : \nA\nB\nbut got :\n"
//                  << buffer2.str() << endl;
//         }

//         // Test case 3: 
//         vector<string> keys3 = {"A", "B", "C", "D"};
//         vector<string> data3 = {"DataA", "DataB", "DataC", "DataD"};
//         vector<vector<string>> edges3 = {{"B", "C"}, {"D"}, {}, {}};
//         Graph<string, string> J(keys3, data3, edges3);
//         stringstream buffer3;
//         streambuf *prevbuf3 = cout.rdbuf(buffer3.rdbuf());
//         J->bfs_tree("A");
//         cout.rdbuf(prevbuf3);
//         if (buffer3.str() != "A\nB C\nD")
//         {
//             cout << "Incorrect bfs tree. Expected : \nA\nB C\nD\nbut got :\n"
//                  << buffer3.str() << endl;
//         }
    
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing bfs tree : " << e.what() << endl;
//     }
// }

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV\n\n")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }

        // Test case 2: Graph with 2 connected nodes
        vector<string> keys2 = {"A", "B"};
        vector<string> data2 = {"DataA", "DataB"};
        vector<vector<string>> edges2 = {{"B"}, {}};
        Graph<string, string> *H = new Graph<string, string>(keys2, data2, edges2);
        stringstream buffer2;
        streambuf *prevbuf2 = cout.rdbuf(buffer2.rdbuf());
        H->bfs_tree("A");  // Now you can use -> because H is a pointer
        cout.rdbuf(prevbuf2);
        if (buffer2.str() != "A\nB")
        {
            cout << "Incorrect bfs tree. Expected : \nA\nB\nbut got :\n"
                << buffer2.str() << endl;
        }

        // Test case 3: 
        vector<string> keys3 = {"A", "B", "C", "D"};
        vector<string> data3 = {"DataA", "DataB", "DataC", "DataD"};
        vector<vector<string>> edges3 = {{"B", "C"}, {"D"}, {}, {}};
        Graph<string, string> *J = new Graph<string, string>(keys3, data3, edges3);
        stringstream buffer3;
        streambuf *prevbuf3 = cout.rdbuf(buffer3.rdbuf());
        J->bfs_tree("A");  // Now you can use -> because J is a pointer
        cout.rdbuf(prevbuf3);
        if (buffer3.str() != "A\nB C\nD")
        {
            cout << "Incorrect bfs tree. Expected : \nA\nB C\nD\nbut got :\n"
                << buffer3.str() << endl;
        }

        // Test case 4: Boolean keys
        vector<bool> keys4 = {true, false};
        vector<string> data4 = {"DataTrue", "DataFalse"};
        vector<vector<bool>> edges4 = {{false}, {}};
        Graph<string, bool> *B = new Graph<string, bool>(keys4, data4, edges4);
        stringstream buffer4;
        streambuf *prevbuf4 = cout.rdbuf(buffer4.rdbuf());
        B->bfs_tree("true");  // Now you can use -> because J is a pointer
        cout.rdbuf(prevbuf4);
        if (buffer4.str() != "true\nfalse")
        {
            cout << "Incorrect bfs tree. Expected : \n1\n0\nbut got :\n"
                << buffer4.str() << endl;
        }


        // Test case 5: Integer keys
        vector<int> keys5 = {1, 2, 3, 4};
        vector<string> data5 = {"Data1", "Data2", "Data3", "Data4"};
        vector<vector<int>> edges5 = {{2, 3}, {4}, {}, {}};
        Graph<string, int> *L = new Graph<string, int>(keys5, data5, edges5);
        stringstream buffer5;
        streambuf *prevbuf5 = cout.rdbuf(buffer5.rdbuf());
        L->bfs_tree(1);
        cout.rdbuf(prevbuf5);
        if (buffer5.str() != "1\n2 3\n4")
        {
            cout << "Incorrect bfs tree. Expected : \n1\n2 3\n4\nbut got :\n"
                << buffer5.str() << endl;
        }
        delete L; 

        
        // Test case 6: Float keys
        vector<float> keys6 = {1.1, 2.2, 3.3, 4.4};
        vector<string> data6 = {"Data1.1", "Data2.2", "Data3.3", "Data4.4"};
        vector<vector<float>> edges6 = {{2.2, 3.3}, {4.4}, {}, {}};
        Graph<string, float> *F = new Graph<string, float>(keys6, data6, edges6);
        stringstream buffer6;
        streambuf *prevbuf6 = cout.rdbuf(buffer6.rdbuf());
        F->bfs_tree(1.1);
        cout.rdbuf(prevbuf6);
        if (buffer6.str() != "1.1\n2.2 3.3\n4.4")
        {
            cout << "Incorrect bfs tree. Expected : \n1.1\n2.2 3.3\n4.4\nbut got :\n"
                << buffer6.str() << endl;
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
    // test_print_path(G);
    //test_edge_class(G);
    test_bfs_tree(G);

    cout << "Testing completed" << endl;

    // delete G;
    // delete H;
    // delete J;

    return 0;
}