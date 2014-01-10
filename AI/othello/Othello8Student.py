"""     +==========================+========-========*========-========+==========================+
        ||                APPLYING THE MINIMAX ALGORITHM TO THE GAME OF OTHELLO                  ||
        ||                        by M. Stueben (Revised: January 5, 2014)                       ||
        +==========================+========-========*========-========+==========================+

                   QUESTION 1: How should computer code be written?
                   --ANSWER 1: So that others can read it in minimal time.
                   QUESTION 2: How is that accomplished?
                   --ANSWER 2: Make it as English-like as possible, and limit the functions to simple tasks.


ASSIGNMENT: Given a working game of Othello, write a strategy (an n-ply minimax algorithm) to allow the com-
            puter to choose a strong (or at least not weak) move.

THE GAME OTHELLO. Othello (aka Reversi) is a game played by two players on a board with 8 rows and 8 columns
and a set of pieces that can change color during the game. The pieces (aka stones and tiles) are white on one
side and black on the other side. Players alternate placing pieces of their color on an 8 x 8 board. The Human
(BLACK) moves first vs. Computer (WHITE).

   If a row, column, or diagonal of consecutive pieces (no blanks) all of the same color becomes flanked
(touched on both sides) by two pieces of the opposite color (by a piece just played), then the pieces in be-
tween are turned over and all become pieces of the boundary color. Hence, the original name "Reversi." In
fact, every legal move MUST turn the color of some of the opponent's pieces. Below White makes a legal move
and turns three black pieces into three white pieces.

                    ..........         ..........         ..........
                    ..BBBWBW..    -->  .WBBBWBW..    -->  .WWWWWBW..
                    ..........         ..........         ..........
                  White to move        White moves         Result

   If one of the three left-most black pieces was replaced by an empty cell,      +----------------------+
White's move would have been illegal, because no black piece would have changed  1|.  .  .  .  .  .  .  .|
color. If a player cannot legally move, he or she must  pass the move to the     2|.  .  .  .  .  .  .  .|
opponent. The game ends when neither player can legally move. This usually       3|.  .  .  =  .  .  .  .|
occurs  because the board fills up.                                              4|.  .  =  W  B  .  .  .|
                                                                                 5|.  .  .  B  W  =  .  .|
                                                                                 6|.  .  .  .  =  .  .  .|
   Othello has a fixed starting position, but Reversi does not. See diagram.     7|.  .  .  .  .  .  .  .|
Reversi players use a common pool of 64 pieces, but each Othello player has      8|.  .  .  .  .  .  .  .|
his own pile of 32 pieces. If an Othello player plays his final piece--his        +----------------------+
opponent having passed the move on at least one occasion--the player can finish    a  b  c  d  e  f  g  h
making legal moves anyway he wants. Othello is copyrighted (1973), Reversi
(invented prior to 1886) is not. Otherwise, the games are identical.

   In the above diagram, it is always Black to make his first move. Since a legal move must bound consecutive
pieces of the opposite color, Black has only four legal moves: c4, d3, e6, and f5. These positions are in-
dicated by equal signs. In fact, these four moves all lead to the same geometric position either mirrored, or
rotated 180 degrees, or both. So Black's first move is already known by his opponent.

   I will save you some time by giving you a working game in this handout and on line. My default strategy,
will make a legal move and little else. Shouldn't there be some advice on the Internet for how to apply this
algorithm, or how to apply some other strategy? I never found much, and what I did find was pretty abstract.

Note well:

P.S. 1) The command exit() seems to cause errors in Tk graphics.
     2) Tk graphics commands with syntax errors often do NOT stop the program from running. But they
        do print error messages to the console window.
     3) A global variable, say M, cannot be modified unless the word global appears on the first
        line of a function, and a list of the global variables to be modified follows it--e.g.

                                          def doit():
                                              global M

     4) Although global variables should be avoided, we are forced to have one (M, the board) in this program.
        I also made the point matrices (heuristics) global as well.


                                     == The Min-Max Algorithm Explained ==

   Assume we are writing a two-person game (like chess, checkers, tic-tac-toe, or Othello) between two
opponents named white (the computer for us in this Othello assignment) and black (the human in our game). We
wish to produce an AI strategy for the computer to choose its move. Suppose we looked at all possible 4-ply
outcomes. That is, positions four moves away from the current position. Basically we construct a tree of these
positions. We notice that one of these positions is winning for white. So white moves planning to go down the
tree towards the winning position. But black sees this too. So black makes a move to avoid this winning
position. In fact, the positions white can now get to are all weak for white. What happened? White's strategy
was flawed. White needed to look at the best position he/she could get to taking into account black's inter-
ference. And that is just what the minimax algorithm is designed to do.

   Before we even start to think about the minimax algorithm, we must teach the computer to how to tell that
one position is better than another position for black. It is a minimax convention that the higher the
evaluation score, the better for the second player, black. It is often the case in games, that we only have a
rough method to distinguish order among positions. For example in Othello, a position where the computer has
the more corner cells captured is usually better than one where it has fewer corners captured. Given that the
corner cells are the same in two positions, a position with more edge cells captured is usually better than
one with fewer edge cells captured. But, of course as humans, we realize that WHERE the edge cells are located
makes a big difference. It is usually too complicated to write an evaluation function equivalent to the one an
experienced player uses.  However, even a rough evaluation function will be good enough if the computer can
see far enough into the future.

#-------------------------------------------------------------------------------------------------------------
 In Othello, I gave the human (black) and the computer (white) two matrices of points. See below. As the
board changed, the values of these cells also changed. Black's (human) matrix PB changed one way and white's
(computer) matrix PW changed in a different way. Still, I can see much improvement could be made to my cell
evaluations.

def initializePointMatrices():
    global PW, PB
##--The computer's strategy will be based off of this GLOBAL matrix, which will be modified as
#   the board configuration changes. Remember: row (going down) is first:  P[row][col]
    PW = [ [1000,  100,  100,  100,  100,  100,  100, 1000,], # P[0][0], P[0][1], ..., P[0][7]
           [ 100,  -40,  -10,  -10,  -10,  -10,  -40,  100,], # P[1][0], P[1][1], ..., P[1][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[2][0], P[2][1], ..., P[2][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[3][0], P[3][1], ..., P[3][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[4][0], P[4][1], ..., P[4][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[5][0], P[5][1], ..., P[5][7]
           [ 100,  -40,  -10,  -10,  -10,  -10,  -40,  100,], # P[6][0], P[6][1], ..., P[6][7]
           [1000,  100,  100,  100,  100,  100,  100, 1000,],]# P[7][0], P[7][1], ..., P[7][7]
    from copy import deepcopy
    PB = deepcopy(PW)
    return PW, PB
#-------------------------------------------------------------------------------------------------------------

   Below is the evaluation function, boardScore(). Notice that the value of a position in boardScore() is
ALWAYS returned as the human's point values MINUS the computer's point values. Also notice the player is
passed up, checked, and never used. These simple one-line checks will catch many errors early.

def boardScore(player):
   assert player == HUMAN
   computerTotal = 0
   humanTotal    = 0
   for r in range(0, 8):
        for c in range(0, 8):
            if M[r][c] == COMPUTER:
                computerTotal += PW[r][c]
            if M[r][c] == HUMAN:
                humanTotal += PB[r][c]
   return humanTotal - computerTotal
#-------------------------------------------------------------------------------------------------------------

   Having come up with an evaluation function, we now must consider how to create all those candidate boards.
My solution is to have only a SINGLE board (represented by global matrix M). Consequently, I needed a function
to make a move and turn the opponent's stones over, and then (after evaluating the position) return the board
to its state before the move was made. The advantages are no memory leaks, and no holding thousands of boards
in memory. The headers for my two functions are below. The actual code is given in the program.
--------------------------------------------------------------------------------------------------------------

            def makeTheMoveAndTurnOverThePieces(r, c, piecesTurnedOver, player):
                ...

            def takeBackTheMoveAndTurnBackOverThePieces(r, c, piecesTurnedOver, player):
                ...
--------------------------------------------------------------------------------------------------------------

                      IMPORTANT ==> The Steps of the Minimax algorithm <== IMPORTANT

   We are going to have the computer construct a tree in which nodes on every level have children except at
   the bottom, called "the frontier" or "the leaves". Recall that the root node of a tree is at level zero.
   The root will be associated with the initial board on which the computer is asked to make a move.

   The next level is level 1, etc. The nodes of our tree are associated with different legal positions that
   could arise in the future. But each node contains only one piece of data: an integer value (positive, neg-
   ative, or zero). Where do these values come from? The values in the tree are obtained in THREE different
   ways. Either the value of a node is the maximum of its children's values, or the minimum of its children's
   values, or if a node has no children, THEN we use our evaluation function boardScore() applied to the
   corresponding board position to obtain a node's value.


                                       The Minimax Tree for an N-Ply Search

   EXPLANATION 1. The computerMove function has access to the global current position, and is expected to
   return a reasonably good move (row, col). We need FIVE functions to implement this algorithm. The functions
   are listed below. But the functions also make use of the three functions already discussed and implemented
   for you: boardScore, makeTheMoveAndTurnOverThePieces, and takeBackTheMoveAndTurnBackOverThePieces.

       The computerMove() function constructs all possible legal boards where white has made a move.
       Every board position is passed to maxValue(), which returns a value (how black is doing).
       Naturally, computerMove() returns the move associated with the MINIMUM value.

       The maxValue() function constructs all possible legal boards where black has made a move.
       Every board position is passed to either minValue(), or to baseCaseForEvenPlyDepth(). Both
       functions return a value (how black is doing). Naturally, black will choose to make the move
       with the highest value. Consequently, both maxValue() and baseCaseForEvenPlyDepth() return the
       MAXIMUM of its children's values (or values provided by the evaluation function, if there are
       no children).

       The minValue() function constructs all possible legal boards where white has made a move.
       It is the mirror image of the maxValue function. Both minValue() and baseCaseForOddPlyDepth()
       return the MINIMUM of its children's values (or values provided by the evaluation function,
       if there are no children).

       The baseCaseForEvenPlyDepth() function constructs all possible legal boards where black has
       made a move. Each board is given an evaluation value. The higher the score the better for
       black. Naturally, black will choose to make the move with the highest value. Consequently,
       baseCaseForEvenPlyDepth() returns the MAXIMUM of values provided by the evaluation function.

       The baseCaseForOddPlyDepth() function constructs all possible legal boards where white has
       made a move. Each board is given an evaluation value. The higher the score the better for
       black. Naturally, white will choose to make the move with the lowest value. Consequently,
       baseCaseForOddPlyDepth() returns the MINIMUM of values provided by the evaluation function.
       -------------------------------------------------------------------------------------------

   EXPLANATION 2. If our tree has an EVEN number of levels (not counting the zero level at the root), then the
   higher the score, the better this position is for the black, who plays the final move. Since black (the
   human) can be assumed to play the best move, each parent in the next-to-last level (level 3 in a 4-level
   tree) is the MAXIMUM of its children's values. To say this again, the final position that white gives
   black has a value corresponding to the position arising from the best's best move (MAXIMUM of the values)
   in that position.

   The parents in the next level up (level 2 in a 4-level tree) choose the MINIMUM of their children's values.
   To say this again, white will choose a move to minimize the best of black's replies. The next level up
   (level 1 in a 4-ply tree) each parent's value is the MAXIMUM of its children's values. We just analyzed
   this tree from bottom up. Now we begin again and will re-analyze this tree from the top down.

   The function computerMove(depth) has access to the current board position (M for matrix). It must return
   a move (row, col), by considering ALL possible future legal positions down to a certain level (depth). The
   move returned is the move associated with the position that has the MAXIMUM value on level 1 (regardless if
   the ply number is even or odd). Then we alternate from MINIMUM to MAXIMUM all the way down the tree until
   we get to the bottom nodes. The nodes at the bottom with no children get their values from the evaluation
   function (boardScore).
       -------------------------------------------------------------------------------------------

   EXPLANATION 3. To code up this algorithm takes FIVE functions, and some utility functions which have
   already been written for you. Here are the five functions.

    1. computerMove(depth). This is NOT a recursive function. But it calls a recursive function called
    [White picks a move.]   maxValue. Than maxValue calls minValue, which calls maxValue, back and forth until
                            a certain depth is reached. Then one of the two base cases is called. The baseCase
                            function returns some values to minValue (or maxValue), which returns some values
                            to maxValue (or minValue), back and forth as the recursion unwinds until maxValue
                            finally returns a value to the computerMove function. For every move (row, col)
                            the computerMove function makes, it receives a value for that move. The
                            computerMove function finally returns the move (row,col) associated with the
                            MINIMUM of the values it received from maxValue. Why return the minimum? The
                            higher the score the better for black.

                            def computersMove(depth, player):
                                depth = depth-1
                            ----------------------------------------------------------------------------------

    2. maxValue(depth).     This function is recursive in the sense that it calls a function (minValue),
    [Black picks a move.]   which calls maxValue. So it indirectly calls itself. Just like computerMove above,
                            this function considers all possible moves to any position it receives. For every
                            move (row, col) the maxValue function makes to the position it was passed, it
                            receives a value for that move. The maxValue function finally returns the MAXIMUM
                            of the values it receives, hence the name maxValue. Unlike computerMove, this
                            function does not need to remember which move (row, col) produced which value.
                            Why return the maximum value? The higher the score the better for black.

                            # Below, we return the MAXIMUM value of the boards created by appending
                            # black moves.
                            def maxValue(depth, player):
                            #---Initialize and check assertions.
                                global M
                                assert player == HUMAN # = black
                            ----------------------------------------------------------------------------------

    3. minValue(depth).     This function is the mirror of maxValue(depth) except that it returns a MINIMUM,
    [White picks a move.]   not a maximum of the values it receives back. Why return the minimum? The higher
                            the score the better for black.

                            # Below, we return the minimum value of the boards created by appending
                            # white moves.
                            def minValue(depth, player):
                            #---Initialize and check assertions.
                                global M
                                assert player == COMPUTER # = white
                            ----------------------------------------------------------------------------------

    4. baseCaseForEvenPlyDepth(). This function is identical to the maxValue function (and is called from the
    [Black picks a move.]   maxValue function), except that it does not get its points from its children.
                            Instead, it uses an evaluation function. Why return the maximum? The higher the
                            score the better for black.








                            def baseCase(depth, player):
                                global M
                                assert depth == 0, [depth]
                                updateThePointMatrices()
                                maxPlayerValue = float('-inf')
                                ...
                                currentPlayerValue = boardScore(player)
                            ----------------------------------------------------------------------------------

    5. baseCaseForOddPlyDepth(). This function is identical to the minValue function (and is called from the
    [White picks a move.]   minValue function), except that it does not get its points from its children.
                            Instead, it uses an evaluation function. Why return the minimum? The higher the
                            score the better for black.

                            def baseCase(depth, player):
                                global M
                                assert depth == 0, [depth]
                                updateThePointMatrices()
                                minPlayerValue = float('inf')
                                ...
                                currentPlayerValue = boardScore(-player) # <--Note the negative sign.
                            ----------------------------------------------------------------------------------

   Here are some tips in coding this algorithm.

   1. Have the computerMove directly call the baseCaseForEvenPlyDepth function. With a 2-ply tree we can
      ignore the maxValue and minValue functions. Get this program to work. Then change the depth from 2 to 4,
      and only then write the minValue and maxValue functions.

   2. The computerMove function is almost exactly like the minValue function, except that the computerMove
      function must associate particular moves (row, col) with every value it receives back from maxValue.
      Then the computerMove function returns the (or a) move that has the (or a) MINIMUM value.

   3. As you recursively call minValue, maxValue, and baseCase, pass down the modified parameters like this:
      depth-1 and -player.

   4. Place some error checks at the beginning of each function. Assume that you will write the code for a
      4-ply tree.

   5. In my implementation of the minimax algorithm, I only returned black's score for any board position.
      Consequently, I knew throughout the algorithm that THE HIGHER THE SCORE, THE BETTER THE POSITION IS FOR
      BLACK. This invariant made it obvious to me when to return a minimum (when white chose a move) and a
      maximum (when black chose a move).

   6. What does maxValue and minValue do when there are no moves to be made--i.e. near the end of the game
      when there are no children to maximize or minimize values? I simply returned a value of zero:

                                   if setOfMoveValuesAndMoves == []:
                                      return 0

      Is this correct? Probably not. But otherwise I got a run-time error from applying the built-in max (or
      min) function to an empty list. Obviously, the minimax algorithm will not do well if the evaluation
      function is poorly written. Nevertheless, at 4-ply this program is hard to beat, and it makes its moves
      in under five seconds. At 5-ply this program can take up to 15 seconds (a little boring). At 6-ply, its
      moves can go beyond a minute-per-move (too boring). There is a speed-up technique called alpha-beta
      pruning that can make the algorithm go faster, but I did not implement it in my program.

                   +--------------------==<KEYS TO THE KINGDOM>==--------------------+
                   |  NOTE WELL: Coding up the minimax algorithm by yourself is a    |
                   |             significant step in becoming a programmer. Keep     |
                   |             your discussions limited to concepts, syntax, and   |
                   |             advice for debugging. As usual, do NOT look at a    |
                   |             classmate's code until you finish your own program. |
                   |             Good luck.                                          |
                   +-----------------------------------------------------------------+
"""


##############################################<START OF PROGRAM>##############################################
def setUpCanvas(root): # These are the REQUIRED magic lines to enter graphics mode.
    root.title("A Tk/Python Graphics Program") # Your screen size may be different from 1270 x 780.
    canvas = Canvas(root, width = 1270, height = 780, bg = 'GREY30')
    canvas.pack(expand = YES, fill = BOTH)
    return canvas
#----------------------------------------------------------------------------------------------------Othello--

def createMatrix(): # = the initial position, with Black = 1, and white = -1.
    M = [ [0, 0, 0, 0, 0, 0, 0, 0,],
          [0, 0, 0, 0, 0, 0, 0, 0,],
          [0, 0, 0, 0, 0, 0, 0, 0,],
          [0, 0, 0,-1, 1, 0, 0, 0,], # The matrix M is GLOBAL.
          [0, 0, 0, 1,-1, 0, 0, 0,],
          [0, 0, 0, 0, 0, 0, 0, 0,],
          [0, 0, 0, 0, 0, 0, 0, 0,],
          [0, 0, 0, 0, 0, 0, 0, 0,],]
    return M
#----------------------------------------------------------------------------------------------------Othello---

def initializePointMatrices():
    global PW, PB
##--The computer's strategy will be based off of this GLOBAL matrix, which will be modified as
#   the board configuration changes. Remember: row (going down) is first:  P[row][col]
    PW = [ [1000,  100,  100,  100,  100,  100,  100, 1000,], # P[0][0], P[0][1], ..., P[0][7]
           [ 100,  -40,  -10,  -10,  -10,  -10,  -40,  100,], # P[1][0], P[1][1], ..., P[1][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[2][0], P[2][1], ..., P[2][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[3][0], P[3][1], ..., P[3][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[4][0], P[4][1], ..., P[4][7]
           [ 100,  -10,    1,    1,    1,    1,  -10,  100,], # P[5][0], P[5][1], ..., P[5][7]
           [ 100,  -40,  -10,  -10,  -10,  -10,  -40,  100,], # P[6][0], P[6][1], ..., P[6][7]
           [1000,  100,  100,  100,  100,  100,  100, 1000,],]# P[7][0], P[7][1], ..., P[7][7]
    from copy import deepcopy
    PB = deepcopy(PW)
    return PW, PB
#---------------------------------------------------------------------------------------------------Othello--

def updateTheFourCorners():
    global PW, PB
#---1B. Modify upper-left corner cell's values if the HUMAN has taken that corner.
    if M[0][0] == 1:
        if M[0][2] in [0,-1]: PW[0][1] = -50 # bad  move for white (computer)
        if M[2][0] in [0,-1]: PW[1][0] = -50 # bad  move for white (computer)
        PW[1][1] = -50                       # bad  move for white (computer)
        PB[1][1] = 100                       # good move for black (human)

#---2B. Modify upper-right corner cell's values if the HUMAN has taken that corner.
    if M[0][7] == 1:
        if M[0][5] in [0,-1]: PW[0][6] = -50 # bad  move for white (computer)
        if M[2][7] in [0,-1]: PW[1][7] = -50 # bad  move for white (computer)
        PW[1][6] = -50                       # bad  move for white (computer)
        PB[1][6] = 100                       # good move for black (human)

#---3B. Modify lower-left corner cell's values if the HUMAN has taken that corner.
    if M[7][0] == 1:
        if M[5][0] in [0,-1]: PW[6][0] = -50 # bad  move for white (computer)
        if M[7][2] in [0,-1]: PW[7][1] = -50 # bad  move for white (computer)
        PW[6][1] = -50                       # bad  move for white (computer)
        PB[6][1] = 100                       # good move for black (human)

#---4B. Modify lower-right corner cell's values if the HUMAN has taken that corner.
    if M[7][7] == 1:
        if M[7][5] in [0,-1]: PW[7][6] = -50 # bad  move for white (computer)
        if M[5][7] in [0,-1]: PW[6][7] = -50 # bad  move for white (computer)
        PW[6][6] = -50                       # bad  move for white (computer)
        PB[6][6] = 100                       # good move for black (human)
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#---1W. Modify upper-left corner cell's values if the COMPUTER has taken that corner.
    if M[0][0] == -1:
        if M[0][2] in [0,1]: PB[0][1] = -50 # bad  move for black (human)
        if M[2][0] in [0,1]: PB[1][0] = -50 # bad  move for black (human)
        PB[1][1] = -50                      # bad  move for black (human)
        PW[1][1] = 100                      # good move for white (computer)

#---2W. Modify upper-right corner cell's values if the COMPUTER has taken that corner.
    if M[0][7] == -1:
        if M[0][5] in [0,1]: PB[0][6] = -50 # bad  move for black (human)
        if M[2][7] in [0,1]: PB[1][7] = -50 # bad  move for black (human)
        PB[1][6] = -50                      # bad  move for black (human)
        PW[1][6] = 100                      # good move for white (computer)

#---3W. Modify lower-left corner cell's values if the COMPUTER has taken that corner.
    if M[7][0] == -1:
        if M[5][0] in [0,1]: PB[6][0] = -50 # bad  move for black (human)
        if M[7][2] in [0,1]: PB[7][1] = -50 # bad  move for black (human)
        PB[6][1] = -50                      # bad  move for black (human)
        PW[6][1] = 100                      # good move for white (computer)

#---4W. Modify lower-right corner cell's values if the COMPUTER has taken that corner.
    if M[7][7] == -1:
        if M[7][5] in [0,1]: PB[7][6] = -50 # bad  move for black (human)
        if M[5][7] in [0,1]: PB[6][7] = -50 # bad  move for black (human)
        PB[6][6] = -50                      # bad  move for black (human))
        PW[6][6] = 100                      # good move for white (computer)
#----------------------------------------------------------------------------------------------------Othello--

def updateTheMiddleRowsAndColumns():
    global PW, B
    for n in range (2, 6):
        if M[0][n] == -1:
            PW[1][n] =  20 # TOP    row
            PB[1][n] = -10 # TOP    row
        if M[7][n] == -1:
            PW[6][n] =  20 # BOTTOM row
            PB[6][n] = -10 # BOTTOM row
        if M[n][0] == -1:
            PW[n][1] =  20 # LEFT  column
            PB[n][1] = -10 # LEFT  column
        if M[n][7] == -1:
            PW[n][6] =  20 # RIGHT column
            PB[n][6] = -10 # RIGHT column
        if M[0][n] == 1:
            PW[1][n] = -10 # TOP    row
            PB[1][n] =  20 # TOP    row
        if M[7][n] == 1:
            PW[6][n] = -10 # BOTTOM row
            PB[6][n] =  20 # BOTTOM row
        if M[n][0] == 1:
            PW[n][1] = -10 # LEFT  column
            PB[n][1] =  20 # LEFT  column
        if M[n][7] == 1:
            PW[n][6] = -10 # RIGHT column
            PB[n][6] =  20 # RIGHT column
#----------------------------------------------------------------------------------------------------Othello--

def updateThePointMatrices():
    updateTheFourCorners()
    updateTheMiddleRowsAndColumns()
#----------------------------------------------------------------------------------------------------Othello--






def copyMatrixToScreen():
    canvas.create_text(30,30, text="x", fill = 'BLACK', font = ('Helvetica',1))
    for r in range (8):
       for c in range (8):
        if M[r][c] ==  1:
           sx = c*70 + 85
           sy = r*70 + 105
           canvas.create_oval(sx-25,sy-25, sx+25, sy+25, fill = 'BLACK')
        if M[r][c] == -1:
           sx = c*70 + 85
           sy = r*70 + 105
           canvas.create_oval(sx-25,sy-25, sx+25, sy+25, fill = 'WHITE')
    canvas.update()
#----------------------------------------------------------------------------------------------------Othello--

def showComputersMovesInRedOnScreen (r, c, pieces):
#---If white just moved, then make that stone red
    sy = r*70 + 105
    sx = c*70 + 85
    canvas.create_oval(sx-15,sy-15, sx+15, sy+15, fill = 'RED')

#------Turn any black stones pink if they are about to be about to be turned over.
    for r,c in pieces:
           sy = r*70 + 105
           sx = c*70 + 85
           canvas.create_oval(sx-15,sy-15, sx+15, sy+15, fill = 'PINK')
    canvas.update()
    sleep(PAUSE_TIME)
#----------------------------------------------------------------------------------------------------Othello--

def copyOldBoardToScreenInMiniaturizedForm(rr, cc):
 #--erase previous miniature board
    canvas.create_rectangle(650, 400, 821, 567, width = 5, fill    = 'GRAY30')
    ch = chr(9679)
    for r in range (8):
       for c in range (8):
        sx = c*20 + 665
        sy = r*20 + 412
        if M[r][c] ==  1:
           canvas.create_text(sx, sy, text = ch, fill = 'BLACK', font = ('Helvetica', 20, 'bold') )
        if M[r][c] == -1:
           canvas.create_text(sx, sy, text = ch, fill = 'WHITE', font = ('Helvetica', 20, 'bold') )

    canvas.create_text(cc*20 + 665, rr*20 + 413, text = 'B', fill = 'BLACK', \
                             font = ('Helvetica', 9, 'bold') )
    canvas.update()      # make all previous changes to the canvas
#----------------------------------------------------------------------------------------------------Othello--

def score(): # returns the number of black and white disks.
    whiteTotal = 0; blackTotal = 0
    for r in range(8):
      for c in range (8):
        if M[r][c] ==  1: blackTotal += 1
        if M[r][c] == -1: whiteTotal += 1
    return (blackTotal, whiteTotal)
#----------------------------------------------------------------------------------------------------Othello--

def printMatrices(): # <-- This function prints the matrices M , PW, and PB to the console for debugging.
    print('\n Matrix M')
    print ('     0  1  2  3  4  5  6  7')
    print ('  +--------------------------+')







    for r in range(8):
      print (r, '|', end = '')
      for c in range (8):
         if M[r][c] == 1: ch = '#'
         if M[r][c] ==-1: ch = 'O'
         if M[r][c] == 0: ch = '-'
         if M[r][c] not in {-1,0,1}: ch = '?'
         print ("%3s"%ch, end = '')
      print ("  |")
    print ('  +--------------------------+')
    print ('  |human    = # = BLACK  =  1|')
    print ('  |computer = O = WHITE  = -1|')
    print ('  +--------------------------+')
    print ('M[3][0] =', M[3][0])
#   ------------------------------------------------
    print('\n Matrix PW')
    print ('      0    1    2    3    4    5    6    7')
    print ('  +------------------------------------------+')
    for r in range(8):
      print (r, '|', end = '')
      for c in range (8):
         print ("%5d"%PW[r][c], end = '')
      print ("  |")
    print ('  +------------------------------------------+')
#   ------------------------------------------------
    print('\n Matrix PB')
    print ('      0    1    2    3    4    5    6    7')
    print ('  +------------------------------------------+')
    for r in range(8):
      print (r, '|', end = '')
      for c in range (8):
         print ("%5d"%PB[r][c], end = '')
      print ("  |")
    print ('  +------------------------------------------+')
#----------------------------------------------------------------------------------------------------Othello--

def LocateTurnedPieces(r, c, player): # The pieces turned over are of -player's color. A zero in a
    if M[r][c] != 0: return []        # matrix M cell means an empty cell. This function does NOT
    totalFlipped =   []               # turn any pieces over.
 #--case 1 (move right)
    flipped = []
    if c < 6 and M[r][c+1] == -player:
        for n in range(1, 9):
            if c+n > 7 or M[r][c+n] == 0:
                flipped = []
                break
            if M[r][c+n] == player: break
            flipped += ((r,c+n,),)  # <-- We save the cell locations as tuples.
    totalFlipped += flipped

 #--case 2 (move down)
    flipped = []
    if r < 6 and M[r+1][c] == -player:
        for n in range(1, 9):
            if r+n > 7 or M[r+n][c] == 0:
                flipped = []
                break
            if M[r+n][c] == player: break
            flipped += ((r+n,c,),)
    totalFlipped += flipped








 #--case 3 (move up)
    flipped = []
    if r > 1 and M[r-1][c  ] == -player:
        for n in range(1, 9):
            if r-n < 0 or M[r-n][c] == 0:
                flipped = []
                break
            if M[r-n][c] == player: break
            flipped += ((r-n,c,),)
    totalFlipped += flipped

 #--case 4 (move left)
    flipped = []
    if c > 1 and M[r][c-1] == -player:
        for n in range(1, 9):
            if c-n < 0 or M[r][c-n] == 0:
                flipped = []
                break
            if M[r][c-n] == player: break
            flipped += ((r,c-n,),)
    totalFlipped += flipped

 #--case 5 (move down and right)
    flipped = []
    if r < 6 and c < 6 and M[r+1][c+1] == -player:
        for n in range(1, 9):
            if (r+n) > 7 or (c+n) > 7 or M[r+n][c+n] == 0:
                flipped = []
                break
            if M[r+n][c+n] == player: break
            flipped += ((r+n,c+n,),)
    totalFlipped += flipped

 #--case 6 (move up and left)
    flipped = []
    if r > 0 and c > 0 and M[r-1][c-1] == -player:
        for n in range(1, 9):
            if (r-n) < 0 or (c-n) < 0 or M[r-n][c-n] == 0:
                flipped = []
                break
            if M[r-n][c-n] == player: break
            flipped += ((r-n,c-n,),)
    totalFlipped += flipped

#--case 7 (move up and right)
    flipped = []
    if r > 1 and c < 6 and M[r-1][c+1] == -player:
        for n in range(1, 9):
            if (r-n) < 0 or (c+n) > 7 or M[r-n][c+n] == 0:
                flipped = []
                break
            if M[r-n][c+n] == player: break
            flipped += ((r-n,c+n,),)
    totalFlipped += flipped

 #--case 8 (move down and left)
    flipped = []
    if r < 6 and c > 1 and M[r+1][c-1] == -player:
        for n in range(1, 9):
            if (r+n) > 7 or (c-n) < 0 or M[r+n][c-n] == 0:
                flipped = []
                break
            if M[r+n][c-n] == player: break
            flipped += ((r+n,c-n,),)
    totalFlipped += flipped

    return totalFlipped
#----------------------------------------------------------------------------------------------------Othello--
def setUpInitialBoard():
    ch = chr(9679)
    M  = createMatrix()
 #--print title
    canvas.create_text(330, 50, text = "OTHELLO with AI", \
                       fill = 'WHITE',  font = ('Helvetica', 20, 'bold'))
 #--print directions
    stng = "DIRECTIONS:\n1) Black (human) moves first. Click on any unoccupied cell.\n\
2) If a player cannot move, play passes to the opponent. \n3) Game ends when \
no legal move is possible.\n4) The player with the most colors on the board \
wins.\n5) A legal move MUST cause some pieces to turn color."
    canvas.create_text(810, 100, text = stng,  \
                       fill = 'WHITE',  font = ('Helvetica', 10, 'bold'))
 #--draw outer box, with red border
    canvas.create_rectangle(50, 70, 610, 630, width = 1, fill    = 'DARKGREEN')
    canvas.create_rectangle(47, 67, 612, 632, width = 5, outline = 'RED'  )

 #--Draw 7 horizontal and 7 vertical lines to make the cells
    for n in range (1, 8): # draw horizontal lines
       canvas.create_line(50, 70+70*n, 610, 70+70*n, width = 2, fill = 'BLACK')
    for n in range (1, 8):# draw vertical lines
       canvas.create_line(50+70*n,  70, 50+70*n, 630, width = 2, fill = 'BLACK')

 #--Place gold lines to indicate dangerous area to play (optional).
    canvas.create_rectangle(47+73, 67+73, 612-73, 632-73, width = 1, outline = 'GOLD'  )
    canvas.create_rectangle(47+2*71, 67+2*71, 612-2*71, 632-2*71, width = 1, outline = 'GOLD'  )

 #--Place letters at bottom
    tab = " " * 7
    stng = 'a' + tab + 'b' + tab + 'c' + tab + 'd' + tab + 'e' + \
                 tab + 'f' + tab + 'g' + tab + 'h'
    canvas.create_text(325, 647, text = stng, fill = 'DARKBLUE',  font = ('Helvetica', 20, 'bold'))

 #--Place digits on left side
    for n in range (1,9):
        canvas.create_text(30, 35 + n * 70, text = str(n),
                       fill = 'DARKBLUE',  font = ('Helvetica', 20, 'bold'))
 #--copy matrix to screen.
    copyMatrixToScreen()

 #--Place score on screen
    (BLACK, WHITE) = score()
    stng = 'BLACK = ' + str(BLACK) + '\nWHITE  = ' + str(WHITE)
    canvas.create_text(800, 200, text = stng, fill = 'WHITE',  font = ('Helvetica', 20, 'bold'))
    return M
#----------------------------------------------------------------------------------------------------Othello--

def illegalClick(x, y): # Click is not on board or click is on an already-filled cell.
    player = 1 # player = Black
    if x < 52 or x > 609:
        print("Error 1. Mouse is to left or right of board.")
        return True # = mouse position is off the board

    if y < 62 or y > 632:
        print("Error 2.Mouse is above or below the board.")
        return True # = mouse position is off the board

 #--Calculate matrix position
    c = (x-50)//70
    r = (y-70)//70

    if M[r][c] != 0:
        print("ERROR 3: Cell is occupied at r =", r, " c =", c)
        return True      # = cell is occupied




 #--Not next to cell of opposite color
    flag = 0
    if c < 7 and           M[r  ][c+1] == -player: return False
    if r < 7 and           M[r+1][c  ] == -player: return False
    if r > 0 and           M[r-1][c  ] == -player: return False
    if c > 0 and           M[r  ][c-1] == -player: return False
    if r < 7 and c < 7 and M[r+1][c+1] == -player: return False
    if r > 0 and c > 0 and M[r-1][c-1] == -player: return False
    if r > 0 and c < 7 and M[r-1][c+1] == -player: return False
    if r < 7 and c > 0 and M[r+1][c-1] == -player: return False
    print("ERROR 4: no opposite colored neighbors at r =", r, " c =", c)
    return True # = illegal move
#----------------------------------------------------------------------------------------------------Othello--

def legalMove(player): # Check to see if any pieces will be turned over.
    pieces = []
    for r in range(8):
        for c in range(8):
           pieces += LocateTurnedPieces(r, c, player)
        if pieces != []: break
    if pieces ==[]:
       person = 'WHITE'
       if player == 1: person = 'BLACK'
       stng = 'There is no legal move for ' + person
       canvas.create_rectangle(655,260,957,307, width = 0, fill = 'GRAY30')
       canvas.create_text     (800,280,text = stng, fill = 'RED',  font = ('Helvetica', 10, 'bold'))
       return False
    return True
#----------------------------------------------------------------------------------------------------Othello--

def makeMove(r, c, pieces, player):
    global M
    if player not in [1, -1]: exit('ERROR: BAD PLAYER'+ str(player))
    if pieces == []: return
 #--make the player's legal move in matrix
    M[r][c] = player

    if player == COMPUTER:
        showComputersMovesInRedOnScreen(r, c, pieces)

 #--flip pieces to same color as the player
    for elt in pieces:
        M[elt[0]][elt[1]] = player

#--update the screen
    copyMatrixToScreen()

 #--erase old score and previous move
    canvas.create_rectangle(650, 160, 960, 310, width = 5, fill    = 'GRAY30')

 #--print new score
    (BLACK, WHITE) = score()
    stng = 'BLACK = ' + str(BLACK) + '\nWHITE  = ' + str(WHITE)
    canvas.create_text(800, 200, text = stng, \
                       fill = 'WHITE',  font = ('Helvetica', 20, 'bold'))

 #--print previous move on miniature board
    position = "previous move: "+ str(chr(c + 97))+str(r+1)
    canvas.create_text(800, 250, text = position, \
                       fill = 'WHITE',  font = ('Helvetica', 20, 'bold'))

    if player == COMPUTER:
       canvas.create_text(c*20 + 665, r*20 + 413, text = 'W', fill = 'WHITE', \
                             font = ('Helvetica', 9, 'bold') )
#----------------------------------------------------------------------------------------------------Othello--



def quit():
    canvas.create_text(330, 350, text = "GAME OVER", \
                       fill = 'RED',  font = ('Helvetica', 40, 'bold'))
    stng = 'THERE ARE NO LEGAL MOVES FOR EITHER PLAYER.'
    canvas.create_rectangle(655, 260, 955, 300, width = 0, fill = 'GRAY30')
    canvas.create_text(805, 280, text = stng, fill = 'GOLD',  font = ('Helvetica', 9, 'bold'))
#----------------------------------------------------------------------------------------------------Othello--

def totalPointsGainedFromFlippingPieces(player, r, c, pieces):
    if player == COMPUTER:
       total = PW[r][c]          # total = the points associated with the piece played on the board.
       for (rr,cc) in pieces:
           total += PW[rr][cc]   # Add the values associated with the flipped pieces.
       return total
    if player == HUMAN:
       total = PB[r][c]          # total = the points associated with the piece played on the board.
       for (rr,cc) in pieces:
           total += PB[rr][cc]   # Add the values associated with the flipped pieces.
       return total
    exit('ERROR in totalPointsGainedFromFlippingPieces() player = ' + str(player))
#----------------------------------------------------------------------------------------------------Othello--

def displayAllLegalMovesForHumanPlayer(kolor):
    for r in range(0, 8):
        for c in range(0, 8):
           kkolor = kolor
           if M[r][c] == 0:
              total  = len(LocateTurnedPieces(r, c, HUMAN))
           if M[r][c] == 0 and total != 0:
              sy = r*70 + 109
              sx = c*70 + 85
              if r == 0 or c == 0 or r == 7 or c == 7: kkolor = kolor
              canvas.create_text(sx, sy, text = str(total), fill = kkolor, \
                                 font = ('Helvetica', 15, 'bold') )
#----------------------------------------------------------------------------------------------------Othello--

def printTimeSpentThinking(startTime, player):
    assert player in {COMPUTER, HUMAN}
    if player == COMPUTER:
       msg = 'computer thinks for ' + str(round(clock() - startTime - PAUSE_TIME, 2)) + ' seconds'
    if player == HUMAN:
       msg = 'human thinks for '  + str(round(clock() - startTime, 2)) + ' seconds'
    canvas.create_rectangle(650, 340, 950, 365, width = 0, fill = 'GRAY30')
    canvas.create_text(800, 352, text = msg, fill = 'WHITE',  font = ('Helvetica', 12, 'bold'))
#----------------------------------------------------------------------------------------------------Othello--

def boardScore(player):
   assert player == HUMAN
   computerTotal = 0
   humanTotal    = 0
   for r in range(0, 8):
        for c in range(0, 8):
            if M[r][c] == COMPUTER:
                computerTotal += PW[r][c]
            if M[r][c] == HUMAN:
                humanTotal += PB[r][c]
   return humanTotal - computerTotal
#----------------------------------------------------------------------------------------------------Othello--

def makeTheMoveAndTurnOverThePieces(r, c, piecesTurnedOver, player):
    global M

#---Double check that our move is made to an empty cell.
    assert M[r][c] == 0, ['player =', str(player)]

#---Make the move
    M[r][c] = player

#---Double check that the pieces we are turning over are of the opposite color of our player.
    piecesAreOppositeColorOfPlayer = True
    for (r,c) in piecesTurnedOver:
        if M[r][c] != -player:
           piecesAreOppositeColorOfPlayer = False
    assert piecesAreOppositeColorOfPlayer == True

#---Turn the pieces over.
    for (r,c) in piecesTurnedOver:
        M[r][c] = player
#----------------------------------------------------------------------------------------------------Othello--

def takeBackTheMoveAndTurnBackOverThePieces(r, c, piecesTurnedOver, player):
    global M
#---Double check that we are turning back a piece with the same color as player.
    assert M[r][c] == player, ['player =', str(player), 'M[r][c] =', M[r][c], '(r,c) =', (r,c)]

#---Take the move back.
    M[r][c] = 0

#---Double check that the pieces we are turning over are of the same color of our player.
    piecesAreSameColorAsPlayer = True
    for (r,c) in piecesTurnedOver:
        if M[r][c] != player:
           piecesAreSameColorAsPlayer = False
    assert piecesAreSameColorAsPlayer == True

#---Turn the pieces back over.
    for (r,c) in piecesTurnedOver:
        M[r][c] = -player
#----------------------------------------------------------------------------------------------------Othello--

def click(evt): # A legal move is guaranteed to exist.
    displayAllLegalMovesForHumanPlayer('DARKGREEN')

 #--Erase computer's thinking time as computer starts to think about the next move
    canvas.create_rectangle(650, 340, 950, 365, width = 0, fill = 'GREY30')

 #--If move is off board, or cell full, or no opp. neighbor, then CLICK AGAIN.
    if illegalClick(evt.x, evt.y):
        canvas.create_rectangle(660, 270, 940,300, width = 0, fill = 'GRAY30')
        stng = 'Your last mouse click was an ILLEGAL MOVE.'
        canvas.create_text(800, 280, text = stng, fill = 'RED',  font = ('Helvetica', 9, 'bold'))
        return

 #--Find matrix coordinates (c,r) in terms of mouse coordinates (evt.x, evt.y).
    r = (evt.y-70)//70
    c = (evt.x-50)//70

 #--if none of the computer's pieces will be turned, then CLICK AGAIN.
    pieces     = LocateTurnedPieces(r, c, HUMAN)
    if pieces == []:
       canvas.create_rectangle(660, 270, 940,300, width = 0, fill = 'GRAY30')
       stng = 'Your last mouse click did NOT turn a piece.'
       canvas.create_text(800, 280, text = stng, fill = 'ORANGE',  font = ('Helvetica', 9, 'bold'))
       displayAllLegalMovesForHumanPlayer('YELLOW')
       return

 #--Make human move(s) and computer reply/replies.
    copyOldBoardToScreenInMiniaturizedForm(r, c)
    makeMove(r, c, pieces, HUMAN)
##    printTimeSpentThinking(startTime, HUMAN)
    if legalMove(HUMAN) and not legalMove(COMPUTER): return





 #--Make computer reply/replies (1 = BLACK = human, -1 = computer = WHITE)
    if legalMove(COMPUTER):
        startTime = clock()
        bestRow, bestCol, finalPieces = computersMoveX(DEPTH, COMPUTER) # <<<<<<<<<<<<<<<<<<<<<<<<<<<<REMOVE X
        makeMove(bestRow, bestCol, finalPieces, COMPUTER)
        printTimeSpentThinking(startTime, COMPUTER)

    while legalMove(COMPUTER) and not legalMove(HUMAN):
        startTime = clock()
        bestRow, bestCol, finalPieces = computersMoveX(DEPTH, COMPUTER) # <<<<<<<<<<<<<<<<<<<<<<<<<<<<REMOVE X
        makeMove(bestRow, bestCol, finalPieces, COMPUTER)
        printTimeSpentThinking(startTime, COMPUTER)
    displayAllLegalMovesForHumanPlayer('RED')
    startTime = clock()
    if not legalMove(HUMAN) and not legalMove(COMPUTER): quit()

 #-- Note: legal move for human must now necessarily exist.
    return
#----------------------------------------------------------------------------------------------------Othello--

def computersMoveX(depth, player):
    updateThePointMatrices()
#--Make a move that picks up the most points using the point matrix (P).
    bestRow = -1
    bestCol = -1
    maxTotal = -1000
    for r in range(0, 8):
        for c in range(0, 8):
           if M[r][c] == 0:
              pieces = LocateTurnedPieces(r, c, COMPUTER)
              if len(pieces) == 0:
                 continue
              total = totalPointsGainedFromFlippingPieces(COMPUTER, r, c, pieces)
              if maxTotal < total:
                 maxTotal = total
                 bestRow = r
                 bestCol = c
                 finalPieces = pieces
    return(bestRow, bestCol, finalPieces)
#----------------------------------------------------------------------------------------------------Othello--
# Note well: This function begins by creating board positions. It also keeps the (row, col) move associated
#            with each board position. The maxValue and minValue functions do not need to remember the (row,
#            col) moves associated with the positions they create. This function ALWAYS begins with calling
#            the maxValue function, no matter if the ply is even or odd.
def computersMove(depth, player):
    depth = depth-1
    global M
    setOfMoveValuesAndMoves = []        # 1. WRITE THIS FUNCTION
#----------------------------------------------------------------------------------------------------Othello--

def maxValue(depth, player): # Return the MAXIMUM value of the boards created by appending black moves.
#---Initialize and check assertions.
    global M
    assert player  == HUMAN
    setOfMoveValuesAndMoves = []        # 2. WRITE THIS FUNCTION

#----------------------------------------------------------------------------------------------------Othello--
# Return the MINIMUM value of the boards created by appending white moves. Remember, the higher the value,
# the better for black.
def minValue(depth, player):
#---Initialize and check assertions.
    global M
    assert player == COMPUTER # = white
    setOfMoveValuesAndMoves = []        # 3. WRITE THIS FUNCTION
#----------------------------------------------------------------------------------------------------Othello--



# Note that this function is identical to the maxValue function (and is called from the maxValue function),
# except that it does not get its points from its children. Instead, it uses an evaluation function. Why
# return the maximum? The higher the score the better for black.
def baseCaseForEvenPlyDepth(depth, player):
#---Initialize and check assertions.
    global M
    assert depth == 0, [depth]
    updateThePointMatrices()
    maxPlayerValue = float('-inf')      # 4. WRITE THIS FUNCTION
#----------------------------------------------------------------------------------------------------Othello--

#  This function is identical to the minValue function (and is called from the minValue function), except that
#  it does not get its points from its children. Instead, it uses an evaluation function.
def baseCaseForOddPlyDepth(depth, player):
    global M
    assert depth == 0, [depth]
    updateThePointMatrices()
    minPlayerValue = float('inf')       # 5. WRITE THIS FUNCTION
#====================================<GLOBAL CONSTANTS and GLOBAL IMPORTS>====================================

from tkinter  import *   # <-- Use Tkinter in Python 2.x
from time     import clock, sleep
PAUSE_TIME =  1.5
root       =  Tk()
canvas     =  setUpCanvas(root)
PW, PB     =  initializePointMatrices() # <-- Global.
M          =  createMatrix()            # <-- Global, because no variable can be passed to the click function.
HUMAN      =  1 # = Black
COMPUTER   = -1 # = White
DEPTH      =  2 # if DEPTH = 5, moves can take between 11-15 seconds.
#===================================================<MAIN>====================================================

def main():
    root.bind('<Button-1>', click) # 1 = LEFT  mouse button calls the click function.
    root.bind('<Button-3>', click) # 3 = RIGHT mouse button calls the click function.
    setUpInitialBoard()
    root.mainloop()                # The window waits for the click function to be called.
#----------------------------------------------------------------------------------------------------Othello--
if __name__ == '__main__':  main()
###############################################<END OF PROGRAM>###############################################

