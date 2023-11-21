#include <stdio.h>
// Global variables
int pageQIndex = 0;
int pageFaults = 0;

// Function to initialize frames and page queue
void initializeFrames(int maxframes, int frames[], int pageQ[]) {
    // Initialize frames and page queue with -1
    for (int i = 0; i < maxframes; i++) {
        frames[i] = -1;
        pageQ[i] = -1;
    }
}

// Function to display frames
void displayFrames(int maxframes, int frames[]) {
    // Display frames
    for (int i = 0; i < maxframes; i++) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

// Function to check if a page is in frames
int isPageInFrames(int page, int maxframes, int frames[]) {
    // Check if page is in frames
    for (int i = 0; i < maxframes; i++) {
        if (frames[i] == page) {
            return 1; // Page found in frames
        }
    }
    return 0; // Page not found in frames
}

// Function to find an empty frame
int findEmptyFrame(int maxframes, int frames[]) {
    // Find an empty frame
    for (int i = 0; i < maxframes; i++) {
        if (frames[i] == -1) {
            return i; // Return the index of an empty frame
        }
    }
    return -1; // No empty frame found
}

// Function to find the LRU frame
int findLRUFrame(int pageQ[]) {
    // LRU frame is the first page in the queue
    return pageQ[0];
}

// Function to find the optimal frame
int findOptimalFrame(int page, int Str[], int curridx, int maxframes, int maxpages, int frames[]) {
    int farthestIndex = -1;
    int maxDistance = -1;

    // Loop through frames and page reference string to find the optimal frame
    for (int i = 0; i < maxframes; i++) {
        int j;
        for (j = curridx; j < maxpages; j++) {
            if (frames[i] == Str[j]) {
                if (j > maxDistance) {
                    maxDistance = j;
                    farthestIndex = i;
                }
                break;
            }
        }
        if (j == maxpages) {
            return i; // Page not referenced again, so it's the best choice
        }
    }

    return farthestIndex;
}

// FCFS Page Replacement Algorithm
void FCFS(int Str[], int maxframes, int maxpages, int frames[], int pageQ[]) {
    initializeFrames(maxframes, frames, pageQ);
    pageFaults = 0;

    printf("FCFS Page Replacement Algorithm:\n");
    for (int i = 0; i < maxpages; i++) {
        if (!isPageInFrames(Str[i], maxframes, frames)) {
            int emptyFrameIndex = findEmptyFrame(maxframes, frames);
            if (emptyFrameIndex != -1) {
                frames[emptyFrameIndex] = Str[i];
            } else {
                frames[0] = Str[i];
            }
            pageFaults++;
        }

        displayFrames(maxframes, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void LRU(int Str[], int maxframes, int maxpages, int frames[], int pageQ[]) {
    initializeFrames(maxframes, frames, pageQ);
    pageFaults = 0;

    printf("\nLRU Page Replacement Algorithm:\n");
    for (int i = 0; i < maxpages; i++) {
        if (!isPageInFrames(Str[i], maxframes, frames)) {
            int emptyFrameIndex = findEmptyFrame(maxframes, frames);
            if (emptyFrameIndex != -1) {
                frames[emptyFrameIndex] = Str[i];
            } else {
                int lruFrame = findLRUFrame(pageQ);
                for (int j = 0; j < maxframes; j++) {
                    if (pageQ[j] == lruFrame) {
                        frames[j] = Str[i];
                        break;
                    }
                }
            }
            pageFaults++;
        }

        // Update the page queue
        pageQ[pageQIndex] = Str[i];
        pageQIndex++;

        displayFrames(maxframes, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Optimal Page Replacement Algorithm
void Optimal(int Str[], int maxframes, int maxpages, int frames[], int pageQ[]) {
    initializeFrames(maxframes, frames, pageQ);
    pageFaults = 0;

    printf("\nOptimal Page Replacement Algorithm:\n");
    for (int i = 0; i < maxpages; i++) {
        if (!isPageInFrames(Str[i], maxframes, frames)) {
            int emptyFrameIndex = findEmptyFrame(maxframes, frames);
            if (emptyFrameIndex != -1) {
                frames[emptyFrameIndex] = Str[i];
            } else {
                int optimalFrame = findOptimalFrame(Str[i], Str, i + 1, maxframes, maxpages, frames);
                frames[optimalFrame] = Str[i];
            }
            pageFaults++;
        }

        displayFrames(maxframes, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Main function
int main() {
    int maxframes;
    int maxpages;

    // User input: maximum number of frames and pages
    printf("Enter the maximum number of pages: ");
    scanf("%d", &maxpages);
    printf("Enter the maximum number of frames: ");
    scanf("%d", &maxframes);

    int frames[maxframes];
    int pageQ[maxframes];
    int Str[maxpages];

    // User input: page reference string
    printf("Enter the page reference string:\n");
    for (int i = 0; i < maxpages; i++) {
        scanf("%d", &Str[i]);
    }

    // Call page replacement algorithms
    FCFS(Str, maxframes, maxpages, frames, pageQ);
    LRU(Str, maxframes, maxpages, frames, pageQ);
    Optimal(Str, maxframes, maxpages, frames, pageQ);

    return 0;
}
