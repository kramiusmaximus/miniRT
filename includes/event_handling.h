#ifndef INTERACTIONS_H
# define INTERACTIONS_H
# include "main_structs.h"

int 				move_camera(t_vars *vars);
void key_press_hook1(int key, t_vars *vars);
void key_release_hook(int key, t_vars *vars);
int					is_moving(t_nav *nav);
int 				is_rotating(t_nav *nav);
int 				exit_hook(t_vars *vars);
void switch_camera(int i, t_vars *vars);

#endif
