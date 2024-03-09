namespace hellmath {
// TODO: Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
enum class AccountStatus{
troll,
guest,
user,
mod
};
// TODO: Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
enum class Action{
read,
write,
remove
};
// TODO: Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
bool display_post(AccountStatus post, AccountStatus viewer){
    switch(post){
        case AccountStatus::troll:
            if(viewer == AccountStatus::troll)
                return true;
            else
                return false;
        default:
            return true;
    }
}
// TODO: Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
bool permission_check(Action modes, AccountStatus userr){
    switch(modes){
        case Action::remove:
            if(userr == AccountStatus::mod)
                return true;
            else
                return false;
        case Action::write:
            if(userr != AccountStatus::guest)
                return true;
            else
                return false;
        default:
            return true;
    }
}
// TODO: Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.
bool valid_player_combination(AccountStatus user1, AccountStatus user2){
    switch(user1){
        case AccountStatus::troll:
            if(user2 == AccountStatus::troll)
                return true;
            else
                return false;
        case AccountStatus::user:
            if(user2 == AccountStatus::user || user2 == AccountStatus::mod)
                return true;
            else
                return false;
        case AccountStatus::mod:
            if(user2 == AccountStatus::user || user2 == AccountStatus::mod)
                return true;
            else
                return false;
        default:
            return false;
    }
    return (user1 == user2);
}
// TODO: Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
bool has_priority(AccountStatus user1, AccountStatus user2){
    switch(user1){
        case AccountStatus::troll:
            return false;
        case AccountStatus::guest:
            if(user2 == AccountStatus::troll)
                return true;
            else
                return false;            
        case AccountStatus::user:
            if(user2 == AccountStatus::user || user2 == AccountStatus::mod)
                return !true;
            else
                return !false;
        default:
            if(user2 == AccountStatus::mod)
                return !true;
            else
                return !false;
    }
}
}  // namespace hellmath