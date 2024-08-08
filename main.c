#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>

#define MAX_N 10000

void print_select_mode(void)
{
    printf("Please select mode : \n") ;
    
    printf("0 init the file\n") ;
    printf("1 write in information\n") ;
    printf("2 take a look \n") ;
    printf("3 find someone\n") ;
    printf("4 delete someone\n") ;
    printf("5 show my favorite\n") ;
    printf("6 add in my favorite\n") ;
    printf("7 remove my favorite\n") ;
    
    printf("-1 Closed \n") ;
    
    
}

void init_file(void)
{
    FILE* fp = fopen( "contact_people_information" , "w" ) ;
    assert( fp != NULL ) ;
    fclose(fp) ;
    return ;
}

bool change_my_favorite(int n)
{
    printf("Name : ") ;
    char name[100] = {0} ;
    scanf("%s" , name) ;
    putchar('\n') ;
    
    FILE* fp = fopen( "contact_people_information" , "r+" ) ;
    
    char temp_name[100] = {0} ;
    long long int temp_number ;
    int temp_priority ;
    
    bool success = false ;
    while ( fscanf(fp , "%s%lld%d" , temp_name , &temp_number , &temp_priority ) != EOF ) {
        if ( strcmp(temp_name , name) == 0 ) {
            printf("Is this one?(Y/N) : %s %010lld\n" , temp_name , temp_number) ;
            char s[3] ;
            scanf("%s" , s) ;
            putchar('\n') ;
            if ( s[0] == 'Y' ) {
                success = true ;
                fseek(fp , -1 , SEEK_CUR) ;
                fprintf(fp , "%d" , n) ;
                
                break ;
            }
        }
        
        memset( temp_name , 0 , 100 ) ;
    }
    fclose(fp) ;
    return success ;
}



bool find_someone(void)
{
    printf("Choose what do you want to find : \n") ;
    printf("1 Find by name\n") ;
    printf("2 Find by number\n") ;
    
    int mode ;
    scanf("%d" , &mode) ;
    
    if ( mode == 1 ) {
        printf("Find name : ") ;
        char name[100] = {0} ;
        scanf("%s" , name) ;
        putchar('\n') ;
        
        FILE* fp = fopen("contact_people_information" , "r") ;
        assert( fp != NULL ) ;
        
        char temp_name[100] = {0} ;
        long long int temp_number ;
        int priority ;
        
        int find = 0 ;
        while ( fscanf(fp , "%s%lld%d" , temp_name , &temp_number , &priority ) != EOF ) {
            if ( strcmp(temp_name , name) == 0 ) {
                ++find ;
                printf("%d : %s %010lld\n" , find , temp_name , temp_number) ;
            }
            memset( temp_name , 0 , 100 ) ;
        }
        
        fclose(fp) ;
        
        return (find > 0) ;
    }
    else {
        assert( mode == 2 ) ;
        long long int number ;
        printf("Find number : ") ;
        scanf("%lld" , &number) ;
        putchar('\n') ;
        
        FILE* fp = fopen("contact_people_information" , "r") ;
        assert( fp != NULL ) ;
        
        char temp_name[100] = {0} ;
        long long int temp_number ;
        int priority ;
        
        int find = 0 ;
        while ( fscanf(fp , "%s%lld%d" , temp_name , &temp_number , &priority ) != EOF ) {
            if ( temp_number == number ) {
                ++find ;
                printf("%d : %s %010lld\n" , find , temp_name , temp_number) ;
            }
            memset( temp_name , 0 , 100 ) ;
        }
        
        fclose(fp) ;
        
        
        return (find > 0) ;
    }
}

bool write_in_information(void)
{
    printf("Name : ") ;
    char name[100] = {0} ;
    scanf("%s" , name ) ;
    putchar('\n') ;
    
    printf("Number : ") ;
    long long int number ;
    scanf("%lld" , &number) ;
    putchar('\n') ;
    
    
    FILE* fp = fopen( "contact_people_information" , "a+" ) ;
    assert( fp != NULL ) ;
    
    int result = fprintf(fp, "%s %lld 0\n" , name , number) ;
    
    fclose(fp) ;
    return ( result >= 0 ) ;
}

bool traverse_file(int standard)
{
    FILE* fp = fopen( "contact_people_information" , "r" ) ;
    assert( fp != NULL ) ;
    
    char name[100] = {0} ;
    long long int number ;
    int cursor = 1 ;
    int priority ;
    
    while ( fscanf(fp, "%s%lld%d" , name , &number , &priority ) != EOF ) {
        if ( priority >= standard ) {
            printf("%d : %s %010lld\n" , cursor , name , number ) ;
            ++cursor ;
        }
        memset(name , 0 , 100) ;
    }
    
    fclose(fp) ;
    return (cursor >= 2) ;
}


bool delete_someone(void)
{
    char delete_name[100] = {0} ;
    printf("Delete name : ") ;
    scanf("%s" , delete_name) ;
    putchar('\n') ;
    
    FILE* fp = fopen( "contact_people_information" , "r+" ) ;
    assert( fp != NULL ) ;
    
    char string[MAX_N][100] = {{0}} ;
    long long int phone_number[MAX_N] ;
    int priority[MAX_N] ;
    
    int cursor = 0 ;
    char temp[100] = {0} ;
    long long int temp_number ;
    int temp_priority ;
    
    int candidate_cursor = 0 ;
    char candidate_name[MAX_N][100] = {{0}} ;
    long long int candidate_number[MAX_N] ;
    int candidate_priority[MAX_N] ;
    
    while ( fscanf(fp, "%s%lld%d" , temp , &temp_number , &temp_priority ) != EOF ) {
        if ( strcmp(temp , delete_name) != 0 ) {
            strcpy( string[cursor] , temp ) ;
            phone_number[cursor] = temp_number ;
            priority[cursor] = temp_priority ;
            ++cursor ;
        }
        else {
            strcpy( candidate_name[candidate_cursor] , temp ) ;
            candidate_number[candidate_cursor] = temp_number ;
            candidate_priority[candidate_cursor] = temp_priority ;
            ++candidate_cursor ;
        }
        memset(temp, 0, 100) ;
    }
    
    fclose(fp) ;
    FILE* fp2 = fopen( "contact_people_information" , "w" ) ;
    assert( fp2 != NULL ) ;
    long long int record = 0 ;
    for( int i = 0 ; i < cursor ; i++ ) {
        record += fprintf(fp , "%s %lld %d\n" , string[i] , phone_number[i] , priority[i]) ;
    }
    
    printf("Choose which one should delete : \n") ;
    for(int i = 0 ; i < candidate_cursor ; i++) {
        printf("%d : %s %010lld\n" , i + 1 , candidate_name[i] , candidate_number[i] ) ;
    }
    
    int choose ;
    scanf("%d" , &choose) ;
    --choose ;
    
    bool deleted = false ;
    for(int i = 0 ; i < candidate_cursor ; i++) {
        if ( i == choose ) {
            deleted = true ;
            continue ;
        }
        
        record += fprintf(fp2 , "%s %lld %d\n" , candidate_name[i] ,
                          candidate_number[i] , candidate_priority[i] ) ;
    }
    
    
    fclose(fp2) ;
    
    return (deleted) ;
}

int main(void)
{
    printf("Welcome to 通訊錄\n") ;
    print_select_mode() ;

    
    int mode ;
    while ( scanf("%d" , &mode) != EOF ) {
        putchar('\n') ;
        
        switch ( mode ) {
            case 0 :
                init_file() ;
                break ;
            case 1 :
                if (write_in_information() )
                    printf("Success\n") ;
                else
                    printf("Failed\n") ;
                break ;
                
            case 2 :
                if (traverse_file(0))
                    printf("Success\n") ;
                else
                    printf("Failed : the file is empty\n") ;
                break ;
                
            case 3 :
                if ( find_someone() )
                    printf("Success\n") ;
                else
                    printf("No one match the name \n") ;
                break ;
            
            case 4 :
                if ( delete_someone() )
                    printf("Success\n") ;
                else
                    printf("Failed : the file is empty\n") ;
                break ;
            
            case 5 :
                if (traverse_file(1))
                    printf("Success\n") ;
                else
                    printf("Failed : your favorite is empty\n") ;
                break ;
                
                
            case 6 :
                if ( change_my_favorite(1) )
                    printf("Success\n") ;
                else
                    printf("Failed : no such person\n") ;
                break ;
                
            case 7 :
                if ( change_my_favorite(1) )
                    printf("Success\n") ;
                else
                    printf("Failed : no such person\n") ;
                break ;
                    
                
            case -1 :
                printf("Closed\n") ;
                return 0 ;
                
            default :
                printf("please select correct mode \n") ;
        }
        print_select_mode() ;
    }
    
    return 0 ;
}
