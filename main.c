#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>

#define MAX_N 10000

void print_select_mode(void)
{
    printf("Please select mode : \n") ;
    
    printf("1 write in information\n") ;
    printf("2 take a look \n") ;
    printf("3 find someone\n") ;
    printf("4 delete someone\n") ;
    
    printf("-1 Closed \n") ;
    
    
}

bool find_someone(void)
{
    printf("Find name : ") ;
    char name[100] = {0} ;
    scanf("%s" , name) ;
    
    FILE* fp = fopen("contact_people_information" , "r") ;
    assert( fp != NULL ) ;
    
    char temp_name[100] = {0} ;
    long long int temp_number ;
    
    int find = 0 ;
    while ( fscanf(fp , "%s%lld" , temp_name , &temp_number ) != EOF ) {
        if ( strcmp(temp_name , name) == 0 ) {
            ++find ;
            printf("%d : %s %010lld\n" , find , temp_name , temp_number) ;
        }
        memset( temp_name , 0 , 100 ) ;
    }
    
    fclose(fp) ;
    
    
    return (find > 0) ;
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
    
    int result = fprintf(fp, "%s %lld\n" , name , number) ;
    
    fclose(fp) ;
    return ( result >= 0 ) ;
}

bool traverse_file(void)
{
    FILE* fp = fopen( "contact_people_information" , "r" ) ;
    assert( fp != NULL ) ;
    
    char name[100] = {0} ;
    long long int number ;
    int cursor = 1 ;
    while ( fscanf(fp, "%s%lld" , name , &number) != EOF ) {
        printf("%d : %s %010lld\n" , cursor , name , number ) ;
        ++cursor ;
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
    
    int cursor = 0 ;
    char temp[100] = {0} ;
    long long int temp_number ;
    
    int candidate_cursor = 0 ;
    char candidate_name[MAX_N][100] = {{0}} ;
    long long int candidate_number[MAX_N] ;
    
    while ( fscanf(fp, "%s%lld" , temp , &temp_number ) != EOF ) {
        if ( strcmp(temp , delete_name) != 0 ) {
            strcpy( string[cursor] , temp ) ;
            phone_number[cursor] = temp_number ;
            ++cursor ;
        }
        else {
            strcpy( candidate_name[candidate_cursor] , temp ) ;
            candidate_number[candidate_cursor] = temp_number ;
            ++candidate_cursor ;
        }
        memset(temp, 0, 100) ;
    }
    
    fclose(fp) ;
    FILE* fp2 = fopen( "contact_people_information" , "w" ) ;
    assert( fp2 != NULL ) ;
    long long int record = 0 ;
    for( int i = 0 ; i < cursor ; i++ ) {
        record += fprintf(fp , "%s %lld \n" , string[i] , phone_number[i] ) ;
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
        
        record += fprintf(fp2 , "%s %lld\n" , candidate_name[i] , candidate_number[i] ) ;
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
            case 1 :
                if (write_in_information() )
                    printf("Success\n") ;
                else
                    printf("Failed\n") ;
                break ;
                
            case 2 :
                if (traverse_file())
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
