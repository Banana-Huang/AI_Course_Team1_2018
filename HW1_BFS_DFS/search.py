# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    print "Start's successors:"
    no_road = True # Check if the state is no other road
    explored = set() # Check state preventing repeat visiting
    currentState = None 
    frontier = util.Stack() # Use to choose next state
    action = util.Stack() # Store source to goal's action sequence
    frontier.push((problem.getStartState(),None))
    explored.add(problem.getStartState())
    while not frontier.isEmpty():
        currentState = frontier.pop()
        if currentState[1] != None:
            action.push((currentState[0],currentState[1],set())) # store the path to currentState
        for next in problem.getSuccessors(currentState[0]):
            if next[0] not in explored:
                no_road = False
                if problem.isGoalState(next[0]):
                    action.push((next[0],next[1],{'G'})) # Record road and the predecessor's road
                    return [element[1] for element in action.list]
                else:
                    if not action.isEmpty(): # store state's another road on the path
                        temp = action.pop()
                        temp[2].add(next[0])
                        action.push(temp)
                    explored.add(next[0]) # add unexplored successors in to explored set
                    frontier.push((next[0],next[1])) # push successors in to frontier
        if no_road: # if there is no road, it means that you have to choose predecessor's another road to go on
            action.pop()
            rm_State = currentState[0]
            while not action.isEmpty(): # Check whether predecessor has road to choose
                temp = action.pop()
                temp[2].remove(rm_State)
                rm_State = temp[0]
                if temp[2]:
                    action.push(temp)
                    break
        no_road = True          
    print "No goal found\nPlease press red cross to leave...."
    return ['Stop']

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    explored = set() # Check state preventing repeat visiting
    action = {} # Record the action
    currentState = None 
    predecessor = None 
    frontier = util.Queue() # Use to choose next state
    frontier.push((problem.getStartState(),None,None))
    explored.add(problem.getStartState())
    while not frontier.isEmpty():
        currentState = frontier.pop()
        predecessor = currentState[2]
        action[currentState[0]] = (currentState[1],predecessor)
        for next in problem.getSuccessors(currentState[0]):
            if next[0] not in explored:
                if problem.isGoalState(next[0]):
                    result = []                    # Get the path from action sequence
                    result.insert(0,next[1])
                    road = action[currentState[0]]
                    while road[0] != None:
                        result.insert(0,road[0])
                        road = action[road[1]]
                    return result
                else:
                    explored.add(next[0]) # Set successors as explored
                    frontier.push((next[0],next[1],currentState[0])) # push successors in to frontier
    print "No goal found\nPlease press red cross to leave...."
    return ['Stop']

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    explored = set()                # Check state preventing repeat visiting
    action = {}                     # Record the action 
    frontier = util.PriorityQueue() # Use to choose next state
    currentCost = None              # Record the current cost
    cost = 0                        # Record the cost between two state
    move = None                     # Record the move like 'South','West','North','East'
    currentState = problem.getStartState()
    frontier.push(problem.getStartState(),0)               # Push the initial state
    action[problem.getStartState()] = ( move, cost, None ) # move, cost, predecessor
    while not frontier.isEmpty():
        currentState = frontier.pop()
        explored.add(currentState)
        if problem.isGoalState(currentState):
            result = []            # Get the path from action sequence
            data = action[currentState]
            while data[2] != None:
                result.insert(0,data[0])
                currentState = data[2]
                data = action[currentState]
            return result
        currentCost = action[currentState][1]
        #next[0]: state next[1]:move next[0]:cost
        for next in problem.getSuccessors(currentState): 
            if next[0] not in explored:
                move = next[1]
                cost = next[2]
                if next[0] not in action:
                    action[next[0]] = ( move,cost+currentCost,currentState)
                else:
                    if action[next[0]][1] > cost + currentCost: 
                        # if currentCost+cost less than the node before record,then update the node 
                        action[next[0]] = ( move, cost+currentCost,currentState)
                frontier.update(next[0],next[2] + currentCost)
    print "No goal found\nPlease press red cross to leave...."
    return ['Stop']

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    explored = set()                # Check state preventing repeat visiting
    action = {}                     # Record the action 
    frontier = util.PriorityQueue() # Use to choose next state
    currentCost = None              # Record the current cost
    cost = 0                        # Record the cost between two state
    move = None                     # Record the move like 'South','West','North','East'
    currentState = problem.getStartState()
    frontier.push(problem.getStartState(),0 + heuristic(currentState, problem))               # Push the initial state
    action[problem.getStartState()] = ( move, cost, None ) # move, cost, predecessor
    while not frontier.isEmpty():
        currentState = frontier.pop()
        explored.add(currentState)
        if problem.isGoalState(currentState):
            result = []            # Get the path from action sequence
            data = action[currentState]
            while data[2] != None:
                result.insert(0,data[0])
                currentState = data[2]
                data = action[currentState]
            return result
        currentCost = action[currentState][1]
        #next[0]: state next[1]:move next[0]:cost
        for next in problem.getSuccessors(currentState): 
            if next[0] not in explored:
                move = next[1]
                cost = next[2]
                if next[0] not in action:
                    action[next[0]] = ( move,cost+currentCost,currentState)
                else:
                    if action[next[0]][1] > cost + currentCost: 
                        # if currentCost+cost less than the node before record,then update the node 
                        action[next[0]] = ( move, cost+currentCost,currentState)
                frontier.update(next[0],next[2] + currentCost + heuristic(currentState, problem))
    print "No goal found\nPlease press red cross to leave...."
    return ['Stop']


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
