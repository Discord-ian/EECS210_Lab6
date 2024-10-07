#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void print_all_combinations(int score);

int get_user_input() {
    char input_buffer[128];
    int user_input;
    char *end;
    // Copied from code2 with alterations.
    // strtof and strtol will set the end to input_buffer if conversion cannot be done.
    printf("Enter the NFL Score: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        user_input = strtol(input_buffer, &end, 10);
        if (end == input_buffer) {
            user_input = -1;
        }
    } else {
        user_input = -1;
    }
    if (user_input < 0) {
        printf("Invalid input. Try again.\n");
        return -1;
    }
    if (user_input < 2) {
        printf("Exiting...\n");
        exit(1);
    }
    return user_input;
}

int main() {
    int score;
    printf("Enter 0 or 1 to exit\n");
    while (true) {
        // get_user_input will quit the program if the input is invalid.
        score = get_user_input();
        if (score > 1) {
            print_all_combinations(score);
        }
    }
}

void print_all_combinations(int score) {
    // set up all variables for score.
    const int scores[] = {8, 7, 6, 3, 2};
    // 8pts for touchdown + conversion, 7pt for touchdown + field goal, etc.
    int count = 0;
    // Might as well count the amount of possibles as well.


    // for each possible score,
    // we should see how many of those we can have.
    // nested for loops is A way (but not the best at all) to approach it
    for (int td_conversion = 0; td_conversion <= score/scores[0]; td_conversion++) {
        int current_scores[5];
        current_scores[0] = score - td_conversion * scores[0];
        // Now that we have checked for this iteration of td + 2, now we check the next (aka td+1)
        /* Overall it is a mess but the way it works out is:
         * The first for loop is asking to go through each possibility of touchdown + field goals
         * until we go over the limit (i.e. until we would have too many touchdowns and be at a
         * greater score than what was asked of us.)
         *
         * Each subsequent loop is asking. If we have this much score left (i.e., we have had
         * 1 touch down occur, so how many of these lower point events can still happen?)
         * how many x events could
         * occur?
         *
         * At the very end when each point is accounted for, then we can check each for loop
         * iterator and see the total amount of each action occurred to get us here.
         *
         * There is a more reasonable approach to be had with recursion, however I simply could not
         * get it functional in time.
         */
        for (int td_fieldgoal = 0; td_fieldgoal <= current_scores[0]/scores[1]; td_fieldgoal++) {
            current_scores[1] = current_scores[0] - td_fieldgoal * scores[1];
            // current_scores[1]/scores[2] = if we have x points left to score
            // (which is what current_scores[1] is telling us
            // then how many times can we score a td for it to not go over the goal score?
            for (int td_only = 0; td_only <= current_scores[1]/scores[2]; td_only++) {
                current_scores[2] = current_scores[1] - td_only*scores[2];
                for (int fieldgoal = 0; fieldgoal <= current_scores[2]/scores[3]; fieldgoal++) {
                    current_scores[3] = current_scores[2] - fieldgoal*scores[3];
                    for (int safety = 0; safety <= current_scores[3]/scores[4]; safety++) {
                        current_scores[4] = current_scores[3] - safety*scores[4];
                        // At the bottom , now we see if we've taken care of all the scoring.
                        if (current_scores[4] == 0) {
                            // To print it out, we just check what each of the for loops are at.
                            printf("%d TD + 2pt, %d TD + FG, ", td_conversion, td_fieldgoal);
                            printf("%d TD, %d 3pt FG, ", td_only, fieldgoal);
                            printf("%d Safety\n", safety);
                            count++;
                        }
                    }
                }
            }
        }
    }
    printf("Total possible combinations for %d points: %d\n", score, count);
}
