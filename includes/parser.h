#ifndef PARSER_H
#define PARSER_H

int 		parse_rt(char *rt, t_scene *scene);
int 		process_r(char **args, t_scene *scene);
int 		process_a(char **args, t_scene *scene);
int 		process_c(char **args, t_scene *scene);
int 		process_l(char **args, t_scene *scene);
int 		process_pl(char **args, t_scene *scene);
int 		process_sp(char **args, t_scene *scene);
int 		process_sq(char **args, t_scene *scene);
int 		process_cy(char **args, t_scene *scene);
int 		process_tr(char **args, t_scene *scene);
int 		is_int(char *str);
int 		is_float(char *str);
int 		is_input_color(char *str);
int 		is_coords(char *str);
t_listc		*ft_lstcnew(t_camera *data);
void		ft_lstcadd_front(t_listc **head, t_listc *node);

#endif
