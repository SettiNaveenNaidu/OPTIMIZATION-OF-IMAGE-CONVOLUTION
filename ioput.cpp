#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace cv;
using namespace std;

int main(int argc, char *argv[] ) {
    if ( argc != 3 )
    {
        cout<<argc;
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cout<<argv[2];
    if (stoi(argv[2]) == 0) {
      cout<<"input started";
      Mat image;
      image = imread( argv[1],1);
      imwrite("hho.jpg",image);
      if ( !image.data ) {
          printf("No image data \n");
          return -1;
      }
      //cout<<image.cols;

      vector<vector<int>> pixel_data_b(image.rows, vector<int>(image.cols));
      vector<vector<int>> pixel_data_g(image.rows, vector<int>(image.cols));
      vector<vector<int>> pixel_data_r(image.rows, vector<int>(image.cols));
  	  for (int i=0;i<image.rows;i++) {
  		    for (int j=0;j<image.cols;j++) {
  			       pixel_data_b[i][j] = image.at<Vec3b>(i,j)[0];
               pixel_data_g[i][j] = image.at<Vec3b>(i,j)[1];
               pixel_data_r[i][j] = image.at<Vec3b>(i,j)[2];

  		    }
  	  }
      int rows = pixel_data_b.size();
      int cols = pixel_data_b[0].size();

      //padding the image
      vector<int> empty_row(cols+2,0),row_data;
      row_data = empty_row;
      vector<vector<int>> padded_data_b;
      vector<vector<int>> padded_data_g;
      vector<vector<int>> padded_data_r;
      padded_data_b.push_back(empty_row);
      padded_data_g.push_back(empty_row);
      padded_data_r.push_back(empty_row);
      for (int i=0;i<rows;i++) {
          for (int j=0;j<cols;j++) row_data[j+1] = pixel_data_b[i][j];
          padded_data_b.push_back(row_data);
          for (int j=0;j<cols;j++) row_data[j+1] = pixel_data_g[i][j];
          padded_data_g.push_back(row_data);
          for (int j=0;j<cols;j++) row_data[j+1] = pixel_data_r[i][j];
          padded_data_r.push_back(row_data);
      }
      padded_data_b.push_back(empty_row);
      padded_data_g.push_back(empty_row);
      padded_data_r.push_back(empty_row);

      //writing to txt file
      ofstream Myfile;
      Myfile.open("image_data_b.txt");
      for (int i=0;i<image.rows+2;i++) {
  		    for (int j=0;j<image.cols+2;j++) {
               Myfile<<to_string(padded_data_b[i][j]) << " ";
  		    }
          Myfile<<endl;
  	  }
      //free(padded_data_b);
      //closing file
      Myfile.close();
      Myfile.open("image_data_g.txt");
      for (int i=0;i<image.rows+2;i++) {
  		    for (int j=0;j<image.cols+2;j++) {
               Myfile<<to_string(padded_data_g[i][j]) << " ";
  		    }
          Myfile<<endl;
  	  }
      //free(padded_data_g);
      //closing file
      Myfile.close();
      Myfile.open("image_data_r.txt");
      for (int i=0;i<image.rows+2;i++) {
  		    for (int j=0;j<image.cols+2;j++) {
               Myfile<<to_string(padded_data_r[i][j]) << " ";
  		    }
          Myfile<<endl;
  	  }
      //free(padded_data_r);

      //closing file
      Myfile.close();
    } else if (stoi(argv[2]) == 1) {
      cout<<"output started";
      string out_filename = "output_b.txt";
      char c[3] = {'b','g','r'};
      bool flag = true, flag2 = true;
      Mat conv_img;

      for (int k=0;k<3;k++) {
          vector<vector<int>> conv;
        ifstream Ifile;
        out_filename[7] = c[k];
        Ifile.open(out_filename);
        cout<<"opend file";
        int rows=0, cols = 0;
        bool flag = true;
        string img_str;
        //Ifile >> img_str;

        while(getline(Ifile, img_str)) {
  				int k=0;
          vector<int> res;
  				for (int i=0;i<img_str.length();i++) {
  					if (img_str[i]==' ') {
  						res.push_back(k);
              if (flag) cols++;
  						k=0;
  					} else if (img_str[i] == '\n') cout<<"*";
            else {
  						k*=10;
  						k+=int(img_str[i]) - 48;
  					}
  				}
          conv.push_back(res);
          rows++;
          flag = false;
  				//pixel_data.push_back(row);
  			}
        if (flag2) {
          cout<<rows<<cols;
          Mat image(rows,cols,CV_8UC3,Scalar(0,0,0));
          conv_img = image.clone();
          imwrite("dupe.jpg",conv_img);
          //cout<<conv_img;
          flag2 = false;
        }
        for (int i=0;i<rows;i++) {
          for (int j=0;j<cols;j++) {
            conv_img.at<Vec3b>(i,j)[k] = conv[i][j];
            //cout<<conv[i][j]<<" ";
          }
        }
        //rows = 500;
        //cols = 440;
        Ifile.close();

      }

  		/*uint8_t *kk;
  		kk = (uint8_t *)malloc(res.size()*sizeof(uint8_t));

      for  (int i=0;i<res.size();i++) *(kk+i) = res[i];

      write_into_mat
      string image_name;
      image_name = "";
      image_name += argv[1];
      //image_name[image_name.length() - 4] = '\0';
      image_name += ".jpg";*/
  		cout<<imwrite("conv.jpg",conv_img);
    }
    return 0;
}
