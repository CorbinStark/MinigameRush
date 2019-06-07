#ifndef STATES_H
#define STATES_H

#include "ENGINE/bahamut.h"

struct StateGroup;

enum MinigameState {
    MINIGAME_RUNNING,
    MINIGAME_VICTORY,
    MINIGAME_DEFEAT
};

struct State {
    virtual void enter() {}
    virtual MinigameState update(RenderBatch* batch, vec2 mousePos, int speed) = 0;
    virtual void leave() {}
    virtual ~State() {}
    char* identifier;
    StateGroup* parent;
};

struct StateList {
    State** arr;
    u32 size;
    u32 allocated;
};

struct StateGroup {
    StateList states;
    u32 current;
};

static inline
void push_state(State* state, StateList* list) {
    if (list->allocated == 0) {
        list->allocated = 1;
        list->arr = (State**)realloc(list->arr, 1 * sizeof(State*));
    }
    if (list->size == list->allocated) {
        list->allocated *= 2;
        list->arr = (State**)realloc(list->arr, list->allocated * sizeof(State*));
    }
    list->arr[list->size++] = state;
}

static inline
void pop_state(StateList* list) {
    free(list->arr[list->size]->identifier);
    delete list->arr[list->size];
    list->arr[list->size--] = { 0 };
}

static inline
void erase_state(u32 index, StateList* list) {
    if (index == list->size) {
        pop_state(list);
        return;
    }
    //delete state at index
    free(list->arr[index]->identifier);
    delete list->arr[index];
    list->arr[index] = { 0 };
    //swap all values to push the deleted state to top of array
    for (u32 i = index; i < list->size - 1; ++i) {
        State* temp = list->arr[i];
        list->arr[i] = list->arr[i + 1];
        list->arr[i + 1] = temp;
    }
    list->size--;
}

static inline
void set_state(StateGroup* group, const char* identifier) {
    for (u16 i = 0; i < group->states.size; ++i) {
        if (strcmp(group->states.arr[i]->identifier, identifier) == 0) {
            //leave current state
            group->states.arr[group->current]->leave();
            //enter new state
            group->states.arr[i]->enter();
            group->current = i;
            return;
        }
    }
    BMT_LOG(WARNING, "[%s] State doesn't exist", identifier);
}

static inline
void add_state(StateGroup* group, State* state, const char* identifier) {
    bool firstState = false;
    if (group->states.size == 0) {
        firstState = true;
    }

    for (u16 i = 0; i < group->states.size; ++i) {
        if (strcmp(group->states.arr[i]->identifier, identifier) == 0) {
            BMT_LOG(WARNING, "[%s] State already exists in current group!", identifier);
            return;
        }
    }
    state->identifier = (char*)malloc(strlen(identifier) + 1);
    strcpy(state->identifier, identifier);
    state->parent = group;
    push_state(state, &group->states);

    if (firstState) {
        group->current = 0;
        group->states.arr[0]->enter();
    }
}

static inline
void remove_state(StateGroup* group, const char* identifier) {
    for (u16 i = 0; i < group->states.size; ++i) {
        if (strcmp(group->states.arr[i]->identifier, identifier) == 0) {
            erase_state(i, &group->states);
            return;
        }
    }
    BMT_LOG(WARNING, "[%s] State doesn't exist!", identifier);
}

static inline
MinigameState update_current_state(StateGroup* group, RenderBatch* batch, vec2 mousePos, int speed) {
    return group->states.arr[group->current]->update(batch, mousePos, speed);
}

#endif
