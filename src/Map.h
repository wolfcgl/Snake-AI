#pragma once

#include "SearchableGrid.h"
#include <list>
#include <queue>
#include <unordered_set>
#include <functional>

/*
A map of the game
*/
class Map {
public:
    typedef std::vector<std::vector<SearchableGrid>> content_type;
    typedef content_type::size_type size_type;
    typedef std::priority_queue<SearchableGrid, std::vector<SearchableGrid>, std::greater<SearchableGrid>> min_heap;
    typedef std::priority_queue<SearchableGrid, std::vector<SearchableGrid>, std::less<SearchableGrid>> max_heap;
    typedef std::unordered_set<Point, decltype(Point::hash)*> hash_table;

    Map(const size_type &rowCnt_ = 20, const size_type &colCnt_ = 20);
    ~Map();

    /*
    Return the grid at the point.
    Two versions for const and non-const object.
    */
    SearchableGrid& getGrid(const Point &p);
    const SearchableGrid& getGrid(const Point &p) const;

    /*
    Check if the grid at the point is an unsafe grid.
    Unsafe grid type: snake body, snake head, snake tail, wall

    @param p the point to check
    */
    bool isUnsafe(const Point &p) const;

    /*
    Check if the point is inside the map
    (not include the boundary).

    @param p the point to check
    */
    bool isInside(const Point &p) const;

    /*
    Check whether the map is filled with snake body.
    */
    bool isFilledWithBody() const;

    /*
    Create a food on the map randomly.
    */
    void createFood();

    /*
    Remove food if exists
    */
    void removeFood();

    /*
    Check if there is food on the map.
    */
    bool hasFood() const;

    /*
    Return the food position.
    */
    const Point& getFood() const;

    /*
    Return the count of the rows.
    */
    size_type getRowCount() const;

    /*
    Return the count of the columns.
    */
    size_type getColCount() const;

    /*
    Set whether to show the details of the search algorithm.
    */
    void setShowSearchDetails(const bool &b);
    
    /*
    Find the shortest path from the start
    point to the end point.
    Algorithm reference:
    1. https://en.wikipedia.org/wiki/A*_search_algorithm

    @param from the start point
    @param to the end point
    @param path the result will be stored as a list of Direction
                in this field. If there is no path between the two
                points, the size of this field will be zero.
    */
    void findMinPath(const Point &from, const Point &to, std::list<Direction> &path);

    /*
    Find the longest path from the start
    point to the end point.
    Algorithm reference:
    1. https://en.wikipedia.org/wiki/A*_search_algorithm
    2. https://en.wikipedia.org/wiki/Longest_path_problem

    @param from the start point
    @param to the end point
    @param path the result will be stored as a list of Direction
                in this field. If there is no path between the two
                points, the size of this field will be zero.
    */
    void findMaxPath(const Point &from, const Point &to, std::list<Direction> &path);

    /*
    Calculate the manhatten distance between two points.

    @param from the start point
    @param to the end point
    */
    static unsigned getManhattenDistance(const Point &from, const Point &to);

private:
    Point food = Point::INVALID;

    content_type content;  // The elements on the map

    bool showSearchDetails = false;

    /*
    Check if the grid at the point must be ignored by the search algorithm
    Unsearched grid type: snake body, snake head, snake tail, wall, food

    @param p the point to check
    */
    bool isUnsearch(const Point &p) const;

    /*
    Compute the H(Heuristic) value from the start
    point to the end point.

    @param from the start point
    @param to the end point
    @return the heuristic value
    */
    SearchableGrid::value_type computeH(const Point &from, const Point &to) const;

    /*
    Construct the move path from the start
    point to the end point.

    @param from the start point
    @param to the end point
    @param path the result will be stored as a list of Direction
                in this field. If there is no path between the two
                points, the size of this field will be zero.
    */
    void constructPath(const Point &from, const Point &to, std::list<Direction> &path);

    /*
    Show a visited node on the map. This method is designed for
    showing search details. It first checks if showSearchDetails
    field is true.

    @param n the point of the node
    @param type the new type of the grid at the point n
    */
    void showVisitedNode(const Point &n, const Grid::GridType &type);

    /*
    Initialize map content.
    */
    void init();

    /*
    Get a food position on the map
    WARNING: if there is no space for food,
             this will be an endless loop.

    @return the new food position
    */
    Point getFoodPos() const;
};
